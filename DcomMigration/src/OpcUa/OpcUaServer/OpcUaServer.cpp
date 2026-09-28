#include <iostream>
#include <csignal>

#include "simulation.h"

static volatile UA_Boolean running = UA_TRUE;

static void stopHandler(int signum)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Stopping OPC UA server...");
    running = UA_FALSE;
}

/*
=============================================================================
  OPC UA Address Space Hierarchy (Information Model)
=============================================================================

  [Root] (NS0)
   └── 📁 Objects
        └── 📁 IntelligentMotorA  <-- (NodeId: "Motor.DeviceA" / ObjectNode)
             ├── 📄 CurrentSpeed   <-- (NodeId: "Motor.DeviceA.CurrentSpeed" / Double / RO)
             ├── 📄 TargetSpeed    <-- (NodeId: "Motor.DeviceA.TargetSpeed" / Double / RW)
             ├── 📄 Temperature    <-- (NodeId: "Motor.DeviceA.Temperature" / Double / RO)
             ├── 📄 IsFaulted      <-- (NodeId: "Motor.DeviceA.IsFaulted" / Boolean / RO)
             └── 📄 FalutCode      <-- (NodeId: "Motor.DeviceA.FalutCode" / String / RO)

-----------------------------------------------------------------------------
  * NS  : Namespace Index (Our Custom Nodes use Namespace 1)
  * RO  : Read-Only (UA_ACCESSLEVELMASK_READ)
  * RW  : Read-Write (UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE)
=============================================================================
*/
static void addMotorInformationModel(UA_Server* server)
{
    // Create a parent object of Motor, like a folder
    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;
    oAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"InteligentMotorA");
    oAttr.description = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"Industrial Inteligent Motor Instance");

    UA_NodeId motorObjId = UA_NODEID_STRING(1, (char*)"Motor.DeviceA");
    UA_Server_addObjectNode(
        server, 
        motorObjId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
        UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
        UA_QUALIFIEDNAME(1, (char*)"InteligentMotorA"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
        oAttr, 
        NULL, 
        NULL);

    // Add variable node: CurrentSpeed ​​- Read-only
    UA_VariableAttributes cvAttr = UA_VariableAttributes_default;
    UA_Double currentSpeed = 0.0;
    UA_Variant_setScalar(&cvAttr.value, &currentSpeed, &UA_TYPES[UA_TYPES_DOUBLE]);
    cvAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"CurrentSpeed");
    cvAttr.accessLevel = UA_ACCESSLEVELMASK_READ;
    UA_Server_addVariableNode(
        server, 
        UA_NODEID_STRING(1, (char*)"Motor.DeviceA.CurrentSpeed"),
        motorObjId, 
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, (char*)"CurrentSpeed"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        cvAttr, 
        NULL, 
        NULL);

    // Add variable node: TargetSpeed ​​- Read/Write
    UA_VariableAttributes tvAttr = UA_VariableAttributes_default;
    UA_Double targetSpeed = 0.0;
    UA_Variant_setScalar(&tvAttr.value, &targetSpeed, &UA_TYPES[UA_TYPES_DOUBLE]);
    tvAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"TargetSpeed");
    tvAttr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_Server_addVariableNode(
        server,
        UA_NODEID_STRING(1, (char*)"Motor.DeviceA.TargetSpeed"),
        motorObjId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, (char*)"TargetSpeed"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        tvAttr,
        NULL,
        NULL);

    // Add variable node: Current temperature (Temperature) - Read-only
    UA_VariableAttributes tempAttr = UA_VariableAttributes_default;
    UA_Double temperature = 25.0;
    UA_Variant_setScalar(&tempAttr.value, &temperature, &UA_TYPES[UA_TYPES_DOUBLE]);
    tempAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"Temperature");
    tempAttr.accessLevel = UA_ACCESSLEVELMASK_READ;
    UA_Server_addVariableNode(
        server,
        UA_NODEID_STRING(1, (char*)"Motor.DeviceA.Temperature"),
        motorObjId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, (char*)"Temperature"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        tempAttr,
        NULL,
        NULL);
    
    // Add variable node: Fault flag (IsFaulted) - Read-only
    UA_VariableAttributes faultAttr = UA_VariableAttributes_default;
    UA_Boolean isFaulted = UA_FALSE;
    UA_Variant_setScalar(&faultAttr.value, &isFaulted, &UA_TYPES[UA_TYPES_BOOLEAN]);
    faultAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"IsFaulted");
    faultAttr.accessLevel = UA_ACCESSLEVELMASK_READ;
    UA_Server_addVariableNode(
        server,
        UA_NODEID_STRING(1, (char*)"Motor.DeviceA.IsFaulted"),
        motorObjId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, (char*)"IsFaulted"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        faultAttr,
        NULL,
        NULL);

    // Add Variable Node: Error Code (FaultCode) - Read-only
    UA_VariableAttributes codeAttr = UA_VariableAttributes_default;
    UA_String faultCode = UA_STRING((char*)"NONE");
    UA_Variant_setScalar(&codeAttr.value, &faultCode, &UA_TYPES[UA_TYPES_STRING]);
    codeAttr.displayName = UA_LOCALIZEDTEXT((char*)"en-US", (char*)"FaultCode");
    codeAttr.accessLevel = UA_ACCESSLEVELMASK_READ;
    UA_Server_addVariableNode(
        server,
        UA_NODEID_STRING(1, (char*)"Motor.DeviceA.FaultCode"),
        motorObjId,
        UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
        UA_QUALIFIEDNAME(1, (char*)"FaultCode"),
        UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
        codeAttr,
        NULL,
        NULL);
}

int main()
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    // Create the server foundation and standard configuration (port 4840 is used by default).
    UA_Server* server = UA_Server_new();
    UA_ServerConfig* config = UA_Server_getConfig(server);

    UA_ServerConfig_setDefault(config);
    UA_ServerConfig_addAllEndpoints(config);

    // Constructing a motor information model (set of nodes) in the address space.
    addMotorInformationModel(server);

    UA_UInt64 callbackId = 0;
    UA_Server_addRepeatedCallback(server, deviceSimulationCallback, NULL, 100, &callbackId);

    std::cout << "========================================" << std::endl;
    std::cout << " Start OPC UA Motor Server " << std::endl;
    std::cout << " Connecting to Port 4840... " << std::endl;
    std::cout << " Ctrl + C for finish " << std::endl;
    std::cout << "========================================" << std::endl;

    // Start the server's main loop (it continues to run until the 'running' flag becomes FALSE).
    UA_StatusCode retval = UA_Server_run(server, &running);

    // Cleanup (freeing memory)
    UA_Server_delete(server);
    
    return retval == UA_STATUSCODE_GOOD ? 0 : 1;
}

