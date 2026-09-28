#pragma once

// vcpkg
#include <open62541/server.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server_config_default.h>


void deviceSimulationCallback(UA_Server* server, void* data);
