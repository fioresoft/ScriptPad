

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 00:14:07 2038
 */
/* Compiler settings for Beeper2026.idl:
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

#ifndef __Beeper2026_i_h__
#define __Beeper2026_i_h__

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

#ifndef __IBeeperObj2026_FWD_DEFINED__
#define __IBeeperObj2026_FWD_DEFINED__
typedef interface IBeeperObj2026 IBeeperObj2026;

#endif 	/* __IBeeperObj2026_FWD_DEFINED__ */


#ifndef ___IBeeperObj2026Events_FWD_DEFINED__
#define ___IBeeperObj2026Events_FWD_DEFINED__
typedef interface _IBeeperObj2026Events _IBeeperObj2026Events;

#endif 	/* ___IBeeperObj2026Events_FWD_DEFINED__ */


#ifndef __BeeperObj2026_FWD_DEFINED__
#define __BeeperObj2026_FWD_DEFINED__

#ifdef __cplusplus
typedef class BeeperObj2026 BeeperObj2026;
#else
typedef struct BeeperObj2026 BeeperObj2026;
#endif /* __cplusplus */

#endif 	/* __BeeperObj2026_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IBeeperObj2026_INTERFACE_DEFINED__
#define __IBeeperObj2026_INTERFACE_DEFINED__

/* interface IBeeperObj2026 */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBeeperObj2026;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("245ba3f2-dd08-4973-9e8b-eb0b943a0be9")
    IBeeperObj2026 : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Beep( 
            ULONG ms,
            ULONG f) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBeeperObj2026Vtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBeeperObj2026 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBeeperObj2026 * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBeeperObj2026 * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBeeperObj2026 * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBeeperObj2026 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBeeperObj2026 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBeeperObj2026 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(IBeeperObj2026, Beep)
        HRESULT ( STDMETHODCALLTYPE *Beep )( 
            IBeeperObj2026 * This,
            ULONG ms,
            ULONG f);
        
        END_INTERFACE
    } IBeeperObj2026Vtbl;

    interface IBeeperObj2026
    {
        CONST_VTBL struct IBeeperObj2026Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBeeperObj2026_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBeeperObj2026_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBeeperObj2026_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBeeperObj2026_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBeeperObj2026_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBeeperObj2026_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBeeperObj2026_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBeeperObj2026_Beep(This,ms,f)	\
    ( (This)->lpVtbl -> Beep(This,ms,f) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBeeperObj2026_INTERFACE_DEFINED__ */



#ifndef __Beeper2026Lib_LIBRARY_DEFINED__
#define __Beeper2026Lib_LIBRARY_DEFINED__

/* library Beeper2026Lib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Beeper2026Lib;

#ifndef ___IBeeperObj2026Events_DISPINTERFACE_DEFINED__
#define ___IBeeperObj2026Events_DISPINTERFACE_DEFINED__

/* dispinterface _IBeeperObj2026Events */
/* [uuid] */ 


EXTERN_C const IID DIID__IBeeperObj2026Events;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6c9658a7-601d-4d9f-b923-109fa39d68a9")
    _IBeeperObj2026Events : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IBeeperObj2026EventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IBeeperObj2026Events * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IBeeperObj2026Events * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IBeeperObj2026Events * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IBeeperObj2026Events * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IBeeperObj2026Events * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IBeeperObj2026Events * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IBeeperObj2026Events * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _IBeeperObj2026EventsVtbl;

    interface _IBeeperObj2026Events
    {
        CONST_VTBL struct _IBeeperObj2026EventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IBeeperObj2026Events_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IBeeperObj2026Events_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IBeeperObj2026Events_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IBeeperObj2026Events_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IBeeperObj2026Events_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IBeeperObj2026Events_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IBeeperObj2026Events_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IBeeperObj2026Events_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BeeperObj2026;

#ifdef __cplusplus

class DECLSPEC_UUID("0cdcc8d8-d136-42aa-a4a6-b5872f52274d")
BeeperObj2026;
#endif
#endif /* __Beeper2026Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


