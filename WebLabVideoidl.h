

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Apr 07 21:24:28 2015
 */
/* Compiler settings for WebLabVideo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __WebLabVideoidl_h__
#define __WebLabVideoidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DWebLabVideo_FWD_DEFINED__
#define ___DWebLabVideo_FWD_DEFINED__
typedef interface _DWebLabVideo _DWebLabVideo;
#endif 	/* ___DWebLabVideo_FWD_DEFINED__ */


#ifndef ___DWebLabVideoEvents_FWD_DEFINED__
#define ___DWebLabVideoEvents_FWD_DEFINED__
typedef interface _DWebLabVideoEvents _DWebLabVideoEvents;
#endif 	/* ___DWebLabVideoEvents_FWD_DEFINED__ */


#ifndef __WebLabVideo_FWD_DEFINED__
#define __WebLabVideo_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebLabVideo WebLabVideo;
#else
typedef struct WebLabVideo WebLabVideo;
#endif /* __cplusplus */

#endif 	/* __WebLabVideo_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WebLabVideoLib_LIBRARY_DEFINED__
#define __WebLabVideoLib_LIBRARY_DEFINED__

/* library WebLabVideoLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_WebLabVideoLib;

#ifndef ___DWebLabVideo_DISPINTERFACE_DEFINED__
#define ___DWebLabVideo_DISPINTERFACE_DEFINED__

/* dispinterface _DWebLabVideo */
/* [uuid] */ 


EXTERN_C const IID DIID__DWebLabVideo;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("29D4B94A-A38F-4EE5-B488-773C7B93325C")
    _DWebLabVideo : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DWebLabVideoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DWebLabVideo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DWebLabVideo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DWebLabVideo * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DWebLabVideo * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DWebLabVideo * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DWebLabVideo * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DWebLabVideo * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DWebLabVideoVtbl;

    interface _DWebLabVideo
    {
        CONST_VTBL struct _DWebLabVideoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DWebLabVideo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DWebLabVideo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DWebLabVideo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DWebLabVideo_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DWebLabVideo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DWebLabVideo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DWebLabVideo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DWebLabVideo_DISPINTERFACE_DEFINED__ */


#ifndef ___DWebLabVideoEvents_DISPINTERFACE_DEFINED__
#define ___DWebLabVideoEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DWebLabVideoEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DWebLabVideoEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DC1DA45A-7801-48C9-8E67-E615CFC402B1")
    _DWebLabVideoEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DWebLabVideoEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DWebLabVideoEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DWebLabVideoEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DWebLabVideoEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DWebLabVideoEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DWebLabVideoEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DWebLabVideoEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DWebLabVideoEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DWebLabVideoEventsVtbl;

    interface _DWebLabVideoEvents
    {
        CONST_VTBL struct _DWebLabVideoEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DWebLabVideoEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DWebLabVideoEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DWebLabVideoEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DWebLabVideoEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DWebLabVideoEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DWebLabVideoEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DWebLabVideoEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DWebLabVideoEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebLabVideo;

#ifdef __cplusplus

class DECLSPEC_UUID("1255C724-2D2E-4FDF-9138-A78330C49BD1")
WebLabVideo;
#endif
#endif /* __WebLabVideoLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


