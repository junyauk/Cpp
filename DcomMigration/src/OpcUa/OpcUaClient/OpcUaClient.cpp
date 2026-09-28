#include <iostream>
#include <thread>
#include <chrono>

// --- Wrap the C-language open62541 client header for C++ and include it. ---
extern "C" {
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
}

int main() {
    std::cout << "Starting OPC UA client..." << std::endl;

    // 1. Creating the client object and applying the default configuration
    UA_Client* client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    // 2. Connect to the self-hosted server (localhost:4840).
    std::cout << "Connecting to OPC UA server (opc.tcp://localhost:4840)..." << std::endl;
    UA_StatusCode retval = UA_Client_connect(client, (char*)"opc.tcp://localhost:4840");

    if (retval != UA_STATUSCODE_GOOD) {
        std::cerr << "Connecting to server failed. StatusCode: 0x" << std::hex << retval << std::endl;
        std::cerr << "Confirm OpcUaServer is running." << std::endl;
        UA_Client_delete(client);
        return 1;
    }

    std::cout << "Connecting to OPC UA server succeeded." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // 3. [Write Operation] Try setting the TargetSpeed ​​to 1500.0.
    std::cout << " [1] Write TargetSpeed = 1500.0" << std::endl;
    UA_Variant myVariant;
    UA_Variant_init(&myVariant);
    UA_Double targetSpeed = 1500.0;
    UA_Variant_setScalar(&myVariant, &targetSpeed, &UA_TYPES[UA_TYPES_DOUBLE]);

    // Target the "Motor.DeviceA.TargetSpeed" node within the server and write to it.
    UA_NodeId targetNode = UA_NODEID_STRING(1, (char*)"Motor.DeviceA.TargetSpeed");
    retval = UA_Client_writeValueAttribute(client, targetNode, &myVariant);
    if (retval == UA_STATUSCODE_GOOD) {
        std::cout << "-> Successfully wrote TargetSpeed to server." << std::endl;
    }

    // 4. [Read Operation] Poll the current rotational speed five times.
    std::cout << "\n [2] Monitoring the motor status (5 measurements):" << std::endl;
    UA_NodeId currentSpeedNode = UA_NODEID_STRING(1, (char*)"Motor.DeviceA.CurrentSpeed");

    for (int i = 0; i < 5; ++i) {
        UA_Variant value;
        UA_Variant_init(&value);

        // Retrieve the current value from the server.
        retval = UA_Client_readValueAttribute(client, currentSpeedNode, &value);

        if (retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(&value) && value.type == &UA_TYPES[UA_TYPES_DOUBLE]) {
            UA_Double currentVal = *(UA_Double*)value.data;
            std::cout << " Times: " << (i + 1)
                << " | Current spin speed: " << currentVal << " rpm" << std::endl;
        }
        else {
            std::cerr << "Failed to read attribute. StatusCode: 0x" << std::hex << retval << std::endl;
        }

        UA_Variant_clear(&value); // Freeing memory
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for 0.5 sec
    }

    // 5. Cleanup and disconnection from the server
    std::cout << "----------------------------------------" << std::endl;
    UA_Client_disconnect(client);
    UA_Client_delete(client);

    std::cout << "OPC UA client finished." << std::endl;
    return 0;
}
