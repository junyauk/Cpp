

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for ..\..\Shared\DcomInterface.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DcomInterface_h_h__
#define __DcomInterface_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IDcomDevice_FWD_DEFINED__
#define __IDcomDevice_FWD_DEFINED__
typedef interface IDcomDevice IDcomDevice;

#endif 	/* __IDcomDevice_FWD_DEFINED__ */


#ifndef __DcomDeviceComponent_FWD_DEFINED__
#define __DcomDeviceComponent_FWD_DEFINED__

#ifdef __cplusplus
typedef class DcomDeviceComponent DcomDeviceComponent;
#else
typedef struct DcomDeviceComponent DcomDeviceComponent;
#endif /* __cplusplus */

#endif 	/* __DcomDeviceComponent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_DcomInterface_0000_0000 */
/* [local] */ 

typedef struct tagDcomMotorState
    {
    double currentSpeed;
    double targetSpeed;
    double temperature;
    boolean isFaulted;
    BSTR faultCode;
    } 	DcomMotorState;



extern RPC_IF_HANDLE __MIDL_itf_DcomInterface_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DcomInterface_0000_0000_v0_0_s_ifspec;

#ifndef __IDcomDevice_INTERFACE_DEFINED__
#define __IDcomDevice_INTERFACE_DEFINED__

/* interface IDcomDevice */
/* [unique][local][uuid][object] */ 


EXTERN_C const IID IID_IDcomDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A967CB3-4493-49B1-B94C-2EF365EAF6B6")
    IDcomDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ DcomMotorState *pState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTargetSpeed( 
            /* [in] */ double speed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( 
            /* [out] */ boolean *pSuccess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( 
            /* [out] */ boolean *pSuccess) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetAlarm( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IDcomDeviceVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDcomDevice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDcomDevice * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDcomDevice * This);
        
        DECLSPEC_XFGVIRT(IDcomDevice, GetState)
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IDcomDevice * This,
            /* [out] */ DcomMotorState *pState);
        
        DECLSPEC_XFGVIRT(IDcomDevice, SetTargetSpeed)
        HRESULT ( STDMETHODCALLTYPE *SetTargetSpeed )( 
            IDcomDevice * This,
            /* [in] */ double speed);
        
        DECLSPEC_XFGVIRT(IDcomDevice, Start)
        HRESULT ( STDMETHODCALLTYPE *Start )( 
            IDcomDevice * This,
            /* [out] */ boolean *pSuccess);
        
        DECLSPEC_XFGVIRT(IDcomDevice, Stop)
        HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IDcomDevice * This,
            /* [out] */ boolean *pSuccess);
        
        DECLSPEC_XFGVIRT(IDcomDevice, ResetAlarm)
        HRESULT ( STDMETHODCALLTYPE *ResetAlarm )( 
            IDcomDevice * This);
        
        END_INTERFACE
    } IDcomDeviceVtbl;

    interface IDcomDevice
    {
        CONST_VTBL struct IDcomDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDcomDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDcomDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDcomDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDcomDevice_GetState(This,pState)	\
    ( (This)->lpVtbl -> GetState(This,pState) ) 

#define IDcomDevice_SetTargetSpeed(This,speed)	\
    ( (This)->lpVtbl -> SetTargetSpeed(This,speed) ) 

#define IDcomDevice_Start(This,pSuccess)	\
    ( (This)->lpVtbl -> Start(This,pSuccess) ) 

#define IDcomDevice_Stop(This,pSuccess)	\
    ( (This)->lpVtbl -> Stop(This,pSuccess) ) 

#define IDcomDevice_ResetAlarm(This)	\
    ( (This)->lpVtbl -> ResetAlarm(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDcomDevice_INTERFACE_DEFINED__ */



#ifndef __DcomMigrationLib_LIBRARY_DEFINED__
#define __DcomMigrationLib_LIBRARY_DEFINED__

/* library DcomMigrationLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_DcomMigrationLib;

EXTERN_C const CLSID CLSID_DcomDeviceComponent;

#ifdef __cplusplus

class DECLSPEC_UUID("ED3CD201-5E04-40E9-B6BF-AEB72D9AECDC")
DcomDeviceComponent;
#endif
#endif /* __DcomMigrationLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


