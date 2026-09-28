#include <Windows.h>
#include <iostream>
#include "CDcomDevice.h"
#include "../../Shared/DcomInterface_h.h"
#include "../../Shared/DcomInterface_i.c"

bool g_running = true;

BOOL WINAPI ConsoleHandler(DWORD dwCtrlType)
{
    if (dwCtrlType == CTRL_C_EVENT || dwCtrlType == CTRL_BREAK_EVENT)
    {
        std::cout << "\nReceived a server shutdown signal..." << std::endl;
        g_running = false;
        return TRUE;
    }
    return FALSE;
}

class CDcomDeviceFactory : public IClassFactory
{
public:
    // Implementation of IClassFactory
    STDMETHODIMP  QueryInterface(REFIID riid, void** ppvObject) override
    {
        if (!ppvObject) return E_POINTER;

        if (riid == IID_IUnknown || riid == IID_IClassFactory)
        {
            *ppvObject = static_cast<IClassFactory*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    STDMETHODIMP_(ULONG) AddRef(void) override { return ++m_refCount; }
    STDMETHODIMP_(ULONG) Release(void) override
    {
        ULONG res = --m_refCount;
        if (res == 0)
        {
            delete this;
        }
        return res;
    }
    STDMETHODIMP  CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override
    {
        if (pUnkOuter != nullptr) return CLASS_E_NOAGGREGATION;
        CDcomDevice* pDevice = new (std::nothrow) CDcomDevice();
        if (!pDevice) return E_OUTOFMEMORY;

        HRESULT hr = pDevice->QueryInterface(riid, ppvObject);
        pDevice->Release();
        return hr;
    }
    STDMETHODIMP  LockServer(BOOL fLock) override { return S_OK; }

private:
    std::atomic<ULONG> m_refCount{ 1 };

};

#if 0
int main() {
    // 1. Initialize COM library
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cerr << "COM initialization failed" << std::endl;
        return 1;
    }

    std::cout << "--- [unit test] start checking code  ---" << std::endl;

    // 2. Create class instance manually 
    CDcomDevice* pRawDevice = new CDcomDevice();

    // 3. Check if QueryInterface can work
    IDcomDevice* pDevice = nullptr;
    hr = pRawDevice->QueryInterface(__uuidof(IDcomDevice), reinterpret_cast<void**>(&pDevice));

    if (FAILED(hr)) {
        std::cerr << "【Failed】QueryInterface returns 0x80004002 (E_NOINTERFACE) !" << std::endl;
        std::cerr << "Cause: There might be a cause in CDcomDevice. " << std::endl;
        pRawDevice->Release();
        CoUninitialize();
        return 1;
    }

    std::cout << "【Succeeded】Getting interface by QueryInterface succeeded." << std::endl;

    // 4. Check if motor methods can work
    boolean success = FALSE;
    pDevice->Start(&success);
    std::cout << "-> Started motor" << std::endl;

    // Get status twice and check if the value is changed.
    for (int i = 0; i < 2; ++i) {
        DcomMotorState state;
        hr = pDevice->GetState(&state);
        if (SUCCEEDED(hr)) {
            std::cout << "   Measure " << (i + 1)
                << " | Speed: " << state.currentSpeed << " rpm"
                << " | Temp: " << state.temperature << " C" << std::endl;
            SysFreeString(state.faultCode); // Release BSTR
        }
    }

    // 5. Cleanup
    pDevice->Release();
    CoUninitialize();

    std::cout << "--- [unit test] complete ---" << std::endl;
    return 0;
}

#else
int main()
{
    // 1. Register the handler for "Ctrl + C"
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    // 2. Initialize COM library
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
        std::cerr << "Initializing COM library failed. HRESULT: " << std::hex << hr << std::endl;
        return 1;
    }

    // DCOM security minimum settings (for allowing full access from all clients)
    hr = CoInitializeSecurity(
        NULL,                       // PSECURITY_DESCRIPTOR pSecDesc
        -1,                         // LONG cAuthSvc
        NULL,                       // SOLE_AUTHENTICATION_SERVICE* asAuthSvc
        NULL,                       // void* pReserved1
        RPC_C_AUTHN_LEVEL_NONE,     // DWORD dwAuthnLevel
        RPC_C_IMP_LEVEL_IMPERSONATE,// DWORD dwImpLevel
        NULL,                       // void* AuthList
        EOAC_NONE,                  // DWORD dwCapabilities
        NULL);                      // void* pReserved3

    if (FAILED(hr))
    {
        CoUninitialize();
        std::cerr << "CoInitializeSecurity failed. HRESULT: " << std::hex << hr << std::endl;
        return 1;
    }

    // Create factory and registering to Windows (COM)
    CDcomDeviceFactory* pFactory = new CDcomDeviceFactory();
    DWORD dwCookie = 0;

    hr = CoRegisterClassObject(
        __uuidof(DcomDeviceComponent),
        pFactory,
        CLSCTX_LOCAL_SERVER,    // Registering as local server
        REGCLS_MULTIPLEUSE,
        &dwCookie);

    if (FAILED(hr))
    {
        std::cerr << "Registering the object failed HRESULT: " << std::hex << hr << std::endl;
    }
    else
    {
        std::cout << "========================================" << std::endl;
        std::cout << " The DCOM motor server has started. " << std::endl;
        std::cout << " Waiting for a connection from the client... " << std::endl;
        std::cout << " Press Ctrl + C to exit. " << std::endl;
        std::cout << "========================================" << std::endl;

        // Main loop (waiting for "Ctrl+C")
        while (g_running)
        {
            Sleep(100); // Wait to reduce CPU load
        }

        // Cleanup unregistration
        CoRevokeClassObject(dwCookie);
    }

    pFactory->Release();
    CoUninitialize();

    std::cout << "The server has been shut down safely." << std::endl;

    return 0;
}
#endif
