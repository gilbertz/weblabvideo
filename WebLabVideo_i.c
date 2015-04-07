

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Apr 07 20:08:12 2015
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_WebLabVideoLib,0xA16A48C7,0x51CE,0x4C9E,0x8A,0xB1,0xA5,0x17,0x61,0x90,0x5E,0xA3);


MIDL_DEFINE_GUID(IID, DIID__DWebLabVideo,0x29D4B94A,0xA38F,0x4EE5,0xB4,0x88,0x77,0x3C,0x7B,0x93,0x32,0x5C);


MIDL_DEFINE_GUID(IID, DIID__DWebLabVideoEvents,0xDC1DA45A,0x7801,0x48C9,0x8E,0x67,0xE6,0x15,0xCF,0xC4,0x02,0xB1);


MIDL_DEFINE_GUID(CLSID, CLSID_WebLabVideo,0x1255C724,0x2D2E,0x4FDF,0x91,0x38,0xA7,0x83,0x30,0xC4,0x9B,0xD1);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



