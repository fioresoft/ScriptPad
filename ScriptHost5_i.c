

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IScriptHostApp,0x96B11D43,0x4409,0x469C,0xAC,0xCE,0xA2,0xE4,0x07,0x4A,0xD6,0x86);


MIDL_DEFINE_GUID(IID, LIBID_ScriptHost,0x2C6653D2,0xDC1D,0x435F,0xA0,0x47,0x5D,0x61,0xF7,0xB4,0xE3,0x9C);


MIDL_DEFINE_GUID(IID, DIID__IScriptHostAppEvents,0xA186D01D,0xFA60,0x40F9,0xAC,0x63,0x42,0x5F,0x71,0x3E,0x59,0x80);


MIDL_DEFINE_GUID(CLSID, CLSID_ScriptHostApp,0x831C4BE7,0xDD20,0x4B01,0x85,0xD6,0x55,0x7E,0x58,0xFF,0x39,0x55);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



