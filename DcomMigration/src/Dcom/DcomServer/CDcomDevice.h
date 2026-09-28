#pragma once
#include "DcomInterface_h.h"
#include <atomic>
#include <string>

class CDcomDevice : public IDcomDevice
{
public:
	CDcomDevice();
	virtual ~CDcomDevice() = default;

	// Implementation of the IUnknown interface (a mandatory COM practice)
	STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject) override;
	STDMETHODIMP_(ULONG) AddRef() override;
	STDMETHODIMP_(ULONG) Release() override;

	// --- Implementation of the IDcomDevice interface (defined in IDL) ---
	STDMETHODIMP GetState(DcomMotorState* pState) override;
	STDMETHODIMP SetTargetSpeed(const double speed) override;
	STDMETHODIMP Start(boolean* pSuccess) override;
	STDMETHODIMP Stop(boolean* pSuccess) override;
	STDMETHODIMP ResetAlarm() override;

private:
	std::atomic<ULONG> m_refCount;

	double m_currentSpeed;
	double m_targetSpeed;
	double m_temperature;
	bool m_isFaulted;
	std::wstring m_faultCode; // Use wstring for compatibility of BSTR
};

