#pragma once
#include <string>

struct MotorState
{
	double currentSpeed;	// rpm (readonly)
	double targetSpeed;		// rpm (read/write)
	double temperature;		// Celcious
	bool isFaulted;			// Flag for event
	std::string faultCode;	// Inherit DCOM diagnostics code
};

class IDevice
{
public:
	virtual ~IDevice() = default;

	// Read/Write data
	virtual MotorState GetState() = 0;
	virtual void SetTargetSpeed(const double speed) = 0;

	// Invoke method (RPC / Control)
	virtual bool Start() = 0;		// Motor start
	virtual bool Stop() = 0;		// Motor stop
	virtual void ResetAlarm() = 0;	// Reset (for Diagnostics)
};
