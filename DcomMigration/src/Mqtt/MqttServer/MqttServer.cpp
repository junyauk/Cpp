#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>

#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS{ "tcp://localhost:1883" }; // e.g. "tcp://127.0.0.1:1883"
const std::string CLIENT_ID{ "DcomMigration_MqttServer_MotorA" };
const std::string STATUS_TOPIC{ "factory/deviceA/status" };
const std::string CONTROL_TOPIC{ "factory/deviceA/control" };

double g_currentSpeed = 0.0;
double g_targetSpeed = 0.0;
double g_temperature = 25.0;

class CommandCallback : public virtual mqtt::callback
{
public:
    void message_arrived(mqtt::const_message_ptr msg) override
    {
        std::string topic = msg->get_topic();
        std::string payload = msg->get_payload();

        std::cout << "[MQTT receive] topic: " << topic << " | payload: " << payload << std::endl;

        if (topic == CONTROL_TOPIC)
        {
            try
            {
                double speed = std::stod(payload);
                if (speed >= 0 && speed <= 3000)
                {
                    g_targetSpeed = speed;
                    std::cout << "-> Change the target speed to " << g_targetSpeed << " rpm" << std::endl;
                }
            }
            catch (...)
            {
                std::cerr << "-> Unknown command value was detected." << std::endl;
            }
        }
    }
};

std::string makeJsonPayload(double current, double target, double temp)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "{"
        << "\"currentSpeed\":" << current << ","
        << "\"targetSpeed\":" << target << ","
        << "\"temperature\":" << temp << ","
        << "\"isFaulted\":false,"
        << "\"faultCode\":\"NONE\""
        << "}";
    return oss.str();
}


int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << " Start MQTT Motor server (Publisher) " << std::endl;
    std::cout << " Connecting to broker: " << SERVER_ADDRESS << std::endl;
    std::cout << "========================================" << std::endl;

    // Creating the client object and configuring connection options
    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    CommandCallback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try
    {
        // Connect to the broker
        client.connect(connOpts)->wait();
        std::cout << "Successfully connected to the broker!" << std::endl;

        // Start subscribing to the topic for control commands from the client.
        client.subscribe(CONTROL_TOPIC, 1)->wait();
        std::cout << "Waiting for command topics: " << CONTROL_TOPIC << std::endl;
        std::cout << "Please close this window to exit.\n" << std::endl;

        // Main loop: Convert state to JSON and publish at 1-second intervals; 
        // perform acceleration/deceleration simulation.
        while (true)
        {
            if (g_currentSpeed < g_targetSpeed)
            {
                g_currentSpeed += 50.0;
                if (g_currentSpeed > g_targetSpeed)
                {
                    g_currentSpeed = g_targetSpeed;
                }
            }
            else if (g_currentSpeed > g_targetSpeed)
            {
                g_currentSpeed -= 50.0;
                if (g_currentSpeed < g_targetSpeed)
                {
                    g_currentSpeed = g_targetSpeed;
                }
            }

            // Convert state data into a JSON packet.
            std::string jsonPayload = makeJsonPayload(g_currentSpeed, g_targetSpeed, g_temperature);

            // Publish (send) to the topic "factory/deviceA/status"
            mqtt::message_ptr pubmsg = mqtt::make_message(STATUS_TOPIC, jsonPayload);
            pubmsg->set_qos(1); // QoS settings for guaranteed delivery
            client.publish(pubmsg)->wait();

            std::cout << "[MQTT Transmission] " << jsonPayload << std::endl;

            // Wait for 1.0 sec
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const mqtt::exception &exc)
    {
        std::cerr << "MQTT Error occurred: " << exc.what() << std::endl;
        return 1;
    }
    return 0;
}
