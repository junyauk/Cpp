#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <mqtt/async_client.h>

const std::string SERVER_ADDRESS{ "tcp://localhost:1883" }; // e.g. "tcp://127.0.0.1:1883"
const std::string CLIENT_ID{ "DcomMigration_MqttClient_Operator" };
const std::string STATUS_TOPIC{ "factory/deviceA/status" };
const std::string CONTROL_TOPIC{ "factory/deviceA/control" };

class StatusCallback : public virtual mqtt::callback
{
public:
    void message_arrived(mqtt::const_message_ptr msg) override
    {
        std::string topic = msg->get_topic();
        std::string payload = msg->get_payload();

        if (topic == STATUS_TOPIC)
        {
            std::cout << "[MQTT Data Received] " << payload << std::endl;
        }
    }
};
int main()
{
    std::cout << "Starting MQTT client..." << std::endl;

    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    StatusCallback cb;
    client.set_callback(cb);

    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);

    try
    {
        // Connecting to the broker
        std::cout << "Connecting to MQTT broker..." << std::endl;
        client.connect(connOpts)->wait();
        std::cout << "Connecting to MQTT broker succeeded." << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        // Start subscribing to server status topics.
        client.subscribe(STATUS_TOPIC, 1)->wait();
        std::cout << "Monitoring the motor status (Listening to " << STATUS_TOPIC << ")..." << std::endl;

        // Simply watch the data being received for 3 seconds 
        // (with the asynchronous callback executing automatically).
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // [Command Transmission (Publish)] Try sending the target rotation speed to the motor.
        std::cout << "\n[Sending Command] Instructing TargetSpeed ​​= 1500.0 rpm..." << std::endl;
        std::string commandPayload = "1500.0";
        client.publish(CONTROL_TOPIC, commandPayload.c_str(), commandPayload.length(), 1, false)->wait();

        // Monitor the acceleration and deceleration for another 5 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // Cleanup
        std::cout << "----------------------------------------" << std::endl;
        client.disconnect()->wait();
        std::cout << "MQTT client finished." << std::endl;
    }
    catch (const mqtt::exception& e)
    {
        std::cerr << "MQTT error:" << e.what() << std::endl;
        return 1;
    }
    return 0;
}
