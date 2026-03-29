

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 00:14:07 2038
 */
/* Compiler settings for ScriptHost.idl:
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

#ifndef __ScriptHost5_h__
#define __ScriptHost5_h__

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

#ifndef __IProcs_FWD_DEFINED__
#define __IProcs_FWD_DEFINED__
typedef interface IProcs IProcs;

#endif 	/* __IProcs_FWD_DEFINED__ */


#ifndef __IScriptHostApp_FWD_DEFINED__
#define __IScriptHostApp_FWD_DEFINED__
typedef interface IScriptHostApp IScriptHostApp;

#endif 	/* __IScriptHostApp_FWD_DEFINED__ */


#ifndef __IProc_FWD_DEFINED__
#define __IProc_FWD_DEFINED__
typedef interface IProc IProc;

#endif 	/* __IProc_FWD_DEFINED__ */


#ifndef ___IScriptHostAppEvents_FWD_DEFINED__
#define ___IScriptHostAppEvents_FWD_DEFINED__
typedef interface _IScriptHostAppEvents _IScriptHostAppEvents;

#endif 	/* ___IScriptHostAppEvents_FWD_DEFINED__ */


#ifndef __ScriptHostApp_FWD_DEFINED__
#define __ScriptHostApp_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScriptHostApp ScriptHostApp;
#else
typedef struct ScriptHostApp ScriptHostApp;
#endif /* __cplusplus */

#endif 	/* __ScriptHostApp_FWD_DEFINED__ */


#ifndef __Proc_FWD_DEFINED__
#define __Proc_FWD_DEFINED__

#ifdef __cplusplus
typedef class Proc Proc;
#else
typedef struct Proc Proc;
#endif /* __cplusplus */

#endif 	/* __Proc_FWD_DEFINED__ */


#ifndef __Procs_FWD_DEFINED__
#define __Procs_FWD_DEFINED__

#ifdef __cplusplus
typedef class Procs Procs;
#else
typedef struct Procs Procs;
#endif /* __cplusplus */

#endif 	/* __Procs_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IProcs_INTERFACE_DEFINED__
#define __IProcs_INTERFACE_DEFINED__

/* interface IProcs */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IProcs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5410010A-187C-48B8-BD4A-D0D544313180")
    IProcs : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pCount) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **ppEnum) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long index,
            /* [retval][out] */ VARIANT *pItem) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Next( 
            ULONG cElements,
            /* [out] */ VARIANT **ppvar,
            /* [out] */ ULONG *pcElementFetched) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProcsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProcs * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProcs * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProcs * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProcs * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProcs * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProcs * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProcs * This,
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
        
        DECLSPEC_XFGVIRT(IProcs, get_Count)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IProcs * This,
            /* [retval][out] */ long *pCount);
        
        DECLSPEC_XFGVIRT(IProcs, get__NewEnum)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IProcs * This,
            /* [retval][out] */ IUnknown **ppEnum);
        
        DECLSPEC_XFGVIRT(IProcs, get_Item)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IProcs * This,
            /* [in] */ long index,
            /* [retval][out] */ VARIANT *pItem);
        
        DECLSPEC_XFGVIRT(IProcs, Next)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IProcs * This,
            ULONG cElements,
            /* [out] */ VARIANT **ppvar,
            /* [out] */ ULONG *pcElementFetched);
        
        END_INTERFACE
    } IProcsVtbl;

    interface IProcs
    {
        CONST_VTBL struct IProcsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProcs_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProcs_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProcs_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProcs_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProcs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProcs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProcs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IProcs_get_Count(This,pCount)	\
    ( (This)->lpVtbl -> get_Count(This,pCount) ) 

#define IProcs_get__NewEnum(This,ppEnum)	\
    ( (This)->lpVtbl -> get__NewEnum(This,ppEnum) ) 

#define IProcs_get_Item(This,index,pItem)	\
    ( (This)->lpVtbl -> get_Item(This,index,pItem) ) 

#define IProcs_Next(This,cElements,ppvar,pcElementFetched)	\
    ( (This)->lpVtbl -> Next(This,cElements,ppvar,pcElementFetched) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProcs_INTERFACE_DEFINED__ */


#ifndef __IScriptHostApp_INTERFACE_DEFINED__
#define __IScriptHostApp_INTERFACE_DEFINED__

/* interface IScriptHostApp */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IScriptHostApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("96B11D43-4409-469C-ACCE-A2E4074AD686")
    IScriptHostApp : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Output( 
            /* [in] */ BSTR msg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetTimer( 
            /* [in] */ LONG id,
            /* [in] */ LONG ms,
            /* [retval][out] */ LONG *res) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Box( 
            /* [in] */ BSTR msg) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Beep( 
            /* [in] */ LONG ms,
            /* [in] */ LONG freq) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Procs( 
            /* [retval][out] */ IProcs **ppDisp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IScriptHostAppVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IScriptHostApp * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IScriptHostApp * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IScriptHostApp * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IScriptHostApp * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IScriptHostApp * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IScriptHostApp * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IScriptHostApp * This,
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
        
        DECLSPEC_XFGVIRT(IScriptHostApp, Output)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Output )( 
            IScriptHostApp * This,
            /* [in] */ BSTR msg);
        
        DECLSPEC_XFGVIRT(IScriptHostApp, SetTimer)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetTimer )( 
            IScriptHostApp * This,
            /* [in] */ LONG id,
            /* [in] */ LONG ms,
            /* [retval][out] */ LONG *res);
        
        DECLSPEC_XFGVIRT(IScriptHostApp, Box)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Box )( 
            IScriptHostApp * This,
            /* [in] */ BSTR msg);
        
        DECLSPEC_XFGVIRT(IScriptHostApp, Beep)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Beep )( 
            IScriptHostApp * This,
            /* [in] */ LONG ms,
            /* [in] */ LONG freq);
        
        DECLSPEC_XFGVIRT(IScriptHostApp, get_Procs)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Procs )( 
            IScriptHostApp * This,
            /* [retval][out] */ IProcs **ppDisp);
        
        END_INTERFACE
    } IScriptHostAppVtbl;

    interface IScriptHostApp
    {
        CONST_VTBL struct IScriptHostAppVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScriptHostApp_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IScriptHostApp_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IScriptHostApp_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IScriptHostApp_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IScriptHostApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IScriptHostApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IScriptHostApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IScriptHostApp_Output(This,msg)	\
    ( (This)->lpVtbl -> Output(This,msg) ) 

#define IScriptHostApp_SetTimer(This,id,ms,res)	\
    ( (This)->lpVtbl -> SetTimer(This,id,ms,res) ) 

#define IScriptHostApp_Box(This,msg)	\
    ( (This)->lpVtbl -> Box(This,msg) ) 

#define IScriptHostApp_Beep(This,ms,freq)	\
    ( (This)->lpVtbl -> Beep(This,ms,freq) ) 

#define IScriptHostApp_get_Procs(This,ppDisp)	\
    ( (This)->lpVtbl -> get_Procs(This,ppDisp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IScriptHostApp_INTERFACE_DEFINED__ */


#ifndef __IProc_INTERFACE_DEFINED__
#define __IProc_INTERFACE_DEFINED__

/* interface IProc */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IProc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D833FA16-96D5-4427-B807-B7903AC86FD6")
    IProc : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ LONG *pId) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TryToKill( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IProcVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProc * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProc * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProc * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProc * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProc * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProc * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProc * This,
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
        
        DECLSPEC_XFGVIRT(IProc, get_Name)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IProc * This,
            /* [retval][out] */ BSTR *pName);
        
        DECLSPEC_XFGVIRT(IProc, get_Id)
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Id )( 
            IProc * This,
            /* [retval][out] */ LONG *pId);
        
        DECLSPEC_XFGVIRT(IProc, TryToKill)
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *TryToKill )( 
            IProc * This);
        
        END_INTERFACE
    } IProcVtbl;

    interface IProc
    {
        CONST_VTBL struct IProcVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProc_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProc_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProc_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProc_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IProc_get_Name(This,pName)	\
    ( (This)->lpVtbl -> get_Name(This,pName) ) 

#define IProc_get_Id(This,pId)	\
    ( (This)->lpVtbl -> get_Id(This,pId) ) 

#define IProc_TryToKill(This)	\
    ( (This)->lpVtbl -> TryToKill(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IProc_INTERFACE_DEFINED__ */



#ifndef __ScriptHost_LIBRARY_DEFINED__
#define __ScriptHost_LIBRARY_DEFINED__

/* library ScriptHost */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ScriptHost;

#ifndef ___IScriptHostAppEvents_DISPINTERFACE_DEFINED__
#define ___IScriptHostAppEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IScriptHostAppEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IScriptHostAppEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A186D01D-FA60-40F9-AC63-425F713E5980")
    _IScriptHostAppEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IScriptHostAppEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IScriptHostAppEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IScriptHostAppEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IScriptHostAppEvents * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IScriptHostAppEvents * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IScriptHostAppEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IScriptHostAppEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IScriptHostAppEvents * This,
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
    } _IScriptHostAppEventsVtbl;

    interface _IScriptHostAppEvents
    {
        CONST_VTBL struct _IScriptHostAppEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IScriptHostAppEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IScriptHostAppEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IScriptHostAppEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IScriptHostAppEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IScriptHostAppEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IScriptHostAppEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IScriptHostAppEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IScriptHostAppEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ScriptHostApp;

#ifdef __cplusplus

class DECLSPEC_UUID("831C4BE7-DD20-4B01-85D6-557E58FF3955")
ScriptHostApp;
#endif

EXTERN_C const CLSID CLSID_Proc;

#ifdef __cplusplus

class DECLSPEC_UUID("CDF50684-2694-4D0D-A497-480F891648C7")
Proc;
#endif

EXTERN_C const CLSID CLSID_Procs;

#ifdef __cplusplus

class DECLSPEC_UUID("757E1C36-1444-4C53-B39A-C08E7772A33B")
Procs;
#endif
#endif /* __ScriptHost_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


