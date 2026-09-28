#include <iostream>
#include <csignal>

#include "simulation.h"

void deviceSimulationCallback(UA_Server* server, void* data)
{
	UA_Variant currentVariant;
	UA_Variant targetVariant;
	UA_Variant_init(&currentVariant);
	UA_Variant_init(&targetVariant);

	UA_NodeId currentSpeedNode = UA_NODEID_STRING(1, (char*)"Motor.DeviceA.CurrentSpeed");
	UA_NodeId targetSpeedNode = UA_NODEID_STRING(1, (char*)"Motor.DeviceA.TargetSpeed");

	UA_Server_readValue(server, currentSpeedNode, &currentVariant);
	UA_Server_readValue(server, targetSpeedNode, &targetVariant);

	if (currentVariant.type == &UA_TYPES[UA_TYPES_DOUBLE] && 
		targetVariant.type == &UA_TYPES[UA_TYPES_DOUBLE])
	{
		UA_Double currentSpeed = *(UA_Double*)currentVariant.data;
		UA_Double targetSpeed = *(UA_Double*)targetVariant.data;

		if (currentSpeed < targetSpeed)
		{
			currentSpeed += 50.0;
			if (currentSpeed > targetSpeed) currentSpeed = targetSpeed;
		}
		else if (currentSpeed > targetSpeed)
		{
			currentSpeed -= 50.0;
			if (currentSpeed < targetSpeed) currentSpeed = targetSpeed;
		}

		UA_Variant newCurrentVariant;
		UA_Variant_init(&newCurrentVariant);
		UA_Variant_setScalar(&newCurrentVariant, &currentSpeed, &UA_TYPES[UA_TYPES_DOUBLE]);
		UA_Server_writeValue(server, currentSpeedNode, newCurrentVariant);
	}

	UA_Variant_clear(&currentVariant);
	UA_Variant_clear(&targetVariant);
}

