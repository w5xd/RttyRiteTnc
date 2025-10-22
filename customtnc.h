

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for CustomTnc.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
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

#ifndef __customtnc_h__
#define __customtnc_h__

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

#ifndef __IWlTncCallBack_FWD_DEFINED__
#define __IWlTncCallBack_FWD_DEFINED__
typedef interface IWlTncCallBack IWlTncCallBack;

#endif 	/* __IWlTncCallBack_FWD_DEFINED__ */


#ifndef __IWlTnc_FWD_DEFINED__
#define __IWlTnc_FWD_DEFINED__
typedef interface IWlTnc IWlTnc;

#endif 	/* __IWlTnc_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_CustomTnc_0000_0000 */
/* [local] */ 


enum WlTncCharFlag
    {
        WLTNC_RXEND_CHAR	= 0xa7
    } ;


extern RPC_IF_HANDLE __MIDL_itf_CustomTnc_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CustomTnc_0000_0000_v0_0_s_ifspec;

#ifndef __IWlTncCallBack_INTERFACE_DEFINED__
#define __IWlTncCallBack_INTERFACE_DEFINED__

/* interface IWlTncCallBack */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IWlTncCallBack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("64FA5DF0-968D-492d-BF76-B58E44F4F7AC")
    IWlTncCallBack : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWriteLogUnk( 
            /* [retval][out] */ IUnknown **pUnk) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetWriteLogEntry( 
            /* [retval][out] */ IUnknown **pUnk) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetBaudotLetters( 
            /* [in] */ short Ltrs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddChar( 
            /* [in] */ unsigned char NewChar,
            /* [in] */ short FromWho,
            /* [in] */ short Dupe) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddString( 
            /* [string][in] */ unsigned char *pStr,
            /* [in] */ short FromWho,
            /* [in] */ short Dupe) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplaceTimer( 
            /* [in] */ short TimeMsec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NextNXmitChars( 
            /* [in] */ long Want,
            /* [out] */ long *pGot,
            /* [length_is][size_is][out] */ unsigned char *pChars) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveNXmitChars( 
            /* [in] */ short Count) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_MainHWND( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWlTncCallBackVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWlTncCallBack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWlTncCallBack * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWlTncCallBack * This);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, GetWriteLogUnk)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWriteLogUnk )( 
            IWlTncCallBack * This,
            /* [retval][out] */ IUnknown **pUnk);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, GetWriteLogEntry)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetWriteLogEntry )( 
            IWlTncCallBack * This,
            /* [retval][out] */ IUnknown **pUnk);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, SetBaudotLetters)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetBaudotLetters )( 
            IWlTncCallBack * This,
            /* [in] */ short Ltrs);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, AddChar)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddChar )( 
            IWlTncCallBack * This,
            /* [in] */ unsigned char NewChar,
            /* [in] */ short FromWho,
            /* [in] */ short Dupe);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, AddString)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddString )( 
            IWlTncCallBack * This,
            /* [string][in] */ unsigned char *pStr,
            /* [in] */ short FromWho,
            /* [in] */ short Dupe);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, ReplaceTimer)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReplaceTimer )( 
            IWlTncCallBack * This,
            /* [in] */ short TimeMsec);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, NextNXmitChars)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NextNXmitChars )( 
            IWlTncCallBack * This,
            /* [in] */ long Want,
            /* [out] */ long *pGot,
            /* [length_is][size_is][out] */ unsigned char *pChars);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, RemoveNXmitChars)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveNXmitChars )( 
            IWlTncCallBack * This,
            /* [in] */ short Count);
        
        DECLSPEC_XFGVIRT(IWlTncCallBack, get_MainHWND)
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MainHWND )( 
            IWlTncCallBack * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IWlTncCallBackVtbl;

    interface IWlTncCallBack
    {
        CONST_VTBL struct IWlTncCallBackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWlTncCallBack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWlTncCallBack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWlTncCallBack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWlTncCallBack_GetWriteLogUnk(This,pUnk)	\
    ( (This)->lpVtbl -> GetWriteLogUnk(This,pUnk) ) 

#define IWlTncCallBack_GetWriteLogEntry(This,pUnk)	\
    ( (This)->lpVtbl -> GetWriteLogEntry(This,pUnk) ) 

#define IWlTncCallBack_SetBaudotLetters(This,Ltrs)	\
    ( (This)->lpVtbl -> SetBaudotLetters(This,Ltrs) ) 

#define IWlTncCallBack_AddChar(This,NewChar,FromWho,Dupe)	\
    ( (This)->lpVtbl -> AddChar(This,NewChar,FromWho,Dupe) ) 

#define IWlTncCallBack_AddString(This,pStr,FromWho,Dupe)	\
    ( (This)->lpVtbl -> AddString(This,pStr,FromWho,Dupe) ) 

#define IWlTncCallBack_ReplaceTimer(This,TimeMsec)	\
    ( (This)->lpVtbl -> ReplaceTimer(This,TimeMsec) ) 

#define IWlTncCallBack_NextNXmitChars(This,Want,pGot,pChars)	\
    ( (This)->lpVtbl -> NextNXmitChars(This,Want,pGot,pChars) ) 

#define IWlTncCallBack_RemoveNXmitChars(This,Count)	\
    ( (This)->lpVtbl -> RemoveNXmitChars(This,Count) ) 

#define IWlTncCallBack_get_MainHWND(This,pVal)	\
    ( (This)->lpVtbl -> get_MainHWND(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWlTncCallBack_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_CustomTnc_0000_0001 */
/* [local] */ 


enum WlTncModeMask
    {
        WLTNC_CAN_DO_CW	= 1,
        WLTNC_CAN_DO_PSK	= 2,
        WLTNC_CAN_DO_RTTY	= 4
    } ;

enum WlTncSpeeds
    {
        WLTNC_SPEED_45	= 0,
        WLTNC_SPEED_50	= ( WLTNC_SPEED_45 + 1 ) ,
        WLTNC_SPEED_57	= ( WLTNC_SPEED_50 + 1 ) ,
        WLTNC_SPEED_72	= ( WLTNC_SPEED_57 + 1 ) ,
        WLTNC_SPEED_ASCII	= ( WLTNC_SPEED_72 + 1 ) ,
        WLTNC_SPEED_BPSK	= ( WLTNC_SPEED_ASCII + 1 ) ,
        WLTNC_SPEED_QPSKU	= ( WLTNC_SPEED_BPSK + 1 ) ,
        WLTNC_SPEED_QPSKL	= ( WLTNC_SPEED_QPSKU + 1 ) ,
        WLTNC_SPEED_CW	= ( WLTNC_SPEED_QPSKL + 1 ) 
    } ;


extern RPC_IF_HANDLE __MIDL_itf_CustomTnc_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CustomTnc_0000_0001_v0_0_s_ifspec;

#ifndef __IWlTnc_INTERFACE_DEFINED__
#define __IWlTnc_INTERFACE_DEFINED__

/* interface IWlTnc */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IWlTnc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E85D0135-63FE-45a3-A680-97467B1E7D2C")
    IWlTnc : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFskReverse( 
            /* [in] */ short Xmit,
            /* [in] */ short Rcv) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetFskReverse( 
            /* [out] */ short *pXmit,
            /* [out] */ short *pRcv) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigureTnc( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CanConfigureTnc( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetupCommPort( 
            /* [in] */ short CommPortNumber) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetSpeedIndex( 
            /* [in] */ enum WlTncSpeeds Speed) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PeekProc( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TimerProc( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE XmitNow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiveNow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LettersNow( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_AfcState( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_AfcState( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModeMask( 
            /* [retval][out] */ enum WlTncModeMask *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCallBack( 
            /* [in] */ IWlTncCallBack *pCallBack) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IWlTncVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWlTnc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, SetFskReverse)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFskReverse )( 
            IWlTnc * This,
            /* [in] */ short Xmit,
            /* [in] */ short Rcv);
        
        DECLSPEC_XFGVIRT(IWlTnc, GetFskReverse)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetFskReverse )( 
            IWlTnc * This,
            /* [out] */ short *pXmit,
            /* [out] */ short *pRcv);
        
        DECLSPEC_XFGVIRT(IWlTnc, ConfigureTnc)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigureTnc )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, CanConfigureTnc)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CanConfigureTnc )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, SetupCommPort)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetupCommPort )( 
            IWlTnc * This,
            /* [in] */ short CommPortNumber);
        
        DECLSPEC_XFGVIRT(IWlTnc, SetSpeedIndex)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetSpeedIndex )( 
            IWlTnc * This,
            /* [in] */ enum WlTncSpeeds Speed);
        
        DECLSPEC_XFGVIRT(IWlTnc, PeekProc)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PeekProc )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, TimerProc)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TimerProc )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, XmitNow)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *XmitNow )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, ReceiveNow)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiveNow )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, LettersNow)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LettersNow )( 
            IWlTnc * This);
        
        DECLSPEC_XFGVIRT(IWlTnc, get_AfcState)
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AfcState )( 
            IWlTnc * This,
            /* [retval][out] */ short *pVal);
        
        DECLSPEC_XFGVIRT(IWlTnc, put_AfcState)
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AfcState )( 
            IWlTnc * This,
            /* [in] */ short newVal);
        
        DECLSPEC_XFGVIRT(IWlTnc, get_ModeMask)
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ModeMask )( 
            IWlTnc * This,
            /* [retval][out] */ enum WlTncModeMask *pVal);
        
        DECLSPEC_XFGVIRT(IWlTnc, SetCallBack)
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCallBack )( 
            IWlTnc * This,
            /* [in] */ IWlTncCallBack *pCallBack);
        
        END_INTERFACE
    } IWlTncVtbl;

    interface IWlTnc
    {
        CONST_VTBL struct IWlTncVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWlTnc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWlTnc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWlTnc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWlTnc_SetFskReverse(This,Xmit,Rcv)	\
    ( (This)->lpVtbl -> SetFskReverse(This,Xmit,Rcv) ) 

#define IWlTnc_GetFskReverse(This,pXmit,pRcv)	\
    ( (This)->lpVtbl -> GetFskReverse(This,pXmit,pRcv) ) 

#define IWlTnc_ConfigureTnc(This)	\
    ( (This)->lpVtbl -> ConfigureTnc(This) ) 

#define IWlTnc_CanConfigureTnc(This)	\
    ( (This)->lpVtbl -> CanConfigureTnc(This) ) 

#define IWlTnc_SetupCommPort(This,CommPortNumber)	\
    ( (This)->lpVtbl -> SetupCommPort(This,CommPortNumber) ) 

#define IWlTnc_SetSpeedIndex(This,Speed)	\
    ( (This)->lpVtbl -> SetSpeedIndex(This,Speed) ) 

#define IWlTnc_PeekProc(This)	\
    ( (This)->lpVtbl -> PeekProc(This) ) 

#define IWlTnc_TimerProc(This)	\
    ( (This)->lpVtbl -> TimerProc(This) ) 

#define IWlTnc_XmitNow(This)	\
    ( (This)->lpVtbl -> XmitNow(This) ) 

#define IWlTnc_ReceiveNow(This)	\
    ( (This)->lpVtbl -> ReceiveNow(This) ) 

#define IWlTnc_LettersNow(This)	\
    ( (This)->lpVtbl -> LettersNow(This) ) 

#define IWlTnc_get_AfcState(This,pVal)	\
    ( (This)->lpVtbl -> get_AfcState(This,pVal) ) 

#define IWlTnc_put_AfcState(This,newVal)	\
    ( (This)->lpVtbl -> put_AfcState(This,newVal) ) 

#define IWlTnc_get_ModeMask(This,pVal)	\
    ( (This)->lpVtbl -> get_ModeMask(This,pVal) ) 

#define IWlTnc_SetCallBack(This,pCallBack)	\
    ( (This)->lpVtbl -> SetCallBack(This,pCallBack) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWlTnc_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


