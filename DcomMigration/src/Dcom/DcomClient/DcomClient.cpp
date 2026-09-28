#include <Windows.h>
#include <iostream>
#include <iomanip>
#include "../../Shared/DcomInterface_h.h"
#include "../../Shared/DcomInterface_i.c"

int main()
{
	// 1. Initialize COM library
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		std::cerr << "Initializing COM library failed. HRESULT: 0x" << std::hex << hr << std::endl;
		return 1;
	}
	std::cout << "Starting DCOM client..." << std::endl;

	// 2. Connect to COM server and get the interface pointer
	IDcomDevice* pDevice = nullptr;
	hr = CoCreateInstance(
		__uuidof(DcomDeviceComponent),	// CLSID of server
		NULL,
		CLSCTX_LOCAL_SERVER,			// Use local server
		__uuidof(IDcomDevice),			// Required interface ID
		reinterpret_cast<void**>(&pDevice));
	if (FAILED(hr))
	{
		std::cerr << "Connecting to DCOM server failed. HRESULT: 0x"
			<< std::hex << hr << std::endl;
		std::cerr << "Confirm DcomServer is running." << std::endl;
		CoUninitialize();
		return 1;
	}

	std::cout << "Connecting to DCOM server successed." << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	// 3. Simulation of motor control and status acquisition
	boolean success = FALSE;
	std::cout << "[1] Start the motor..." << std::endl;
	pDevice->Start(&success);
	if (success)
	{
		std::cout << "-> Received the motor start command." << std::endl;
	}

	// Try polling the status five times (monitoring for changes).
	std::cout << "\n[2] Monitoring the motor status (5 measurements):" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		DcomMotorState state;
		hr = pDevice->GetState(&state);
		if (SUCCEEDED(hr))
		{
			// To convert to a wstring and display it, 
			// extract the string from the BSTR and then free it.
			std::wstring fCode(state.faultCode);
			SysFreeString(state.faultCode); // COM Rule: The client is responsible for freeing the received BSTR.

			std::wcout << L" Times: " << (i + 1)
				<< L" | Current spin speed: " << state.currentSpeed << L" rpm"
				<< L" | Target spin speed: " << state.targetSpeed << L" rpm"
				<< L" | Temperature: " << state.temperature << L" Celsius"
				<< L" | Error: " << fCode << std::endl;
		}
		Sleep(500);	// wait for 0.5 sec
	}

	std::cout << "\n[3] Stop morder..." << std::endl;
	pDevice->Stop(&success);
	if (success)
	{
		std::cout << "-> Received motor stop command." << std::endl;
	}

	// Tidyup
	pDevice->Release();
	CoUninitialize();

	std::cout << "----------------------------------------" << std::endl;
	std::cout << "DCOM client finished." << std::endl;
	return 0;

}
