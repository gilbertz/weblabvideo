// WebLabVideo.cpp : CWebLabVideoApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "WebLabVideo.h"
#include "vfw.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWebLabVideoApp theApp;

const GUID CDECL _tlid = { 0xA16A48C7, 0x51CE, 0x4C9E, { 0x8A, 0xB1, 0xA5, 0x17, 0x61, 0x90, 0x5E, 0xA3 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CWebLabVideoApp::InitInstance - DLL 初始化

BOOL CWebLabVideoApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{	
		// TODO: 在此添加您自己的模块初始化代码。

		/* 初始化IPCSDK */
		int nRet = IPC_Init();
		if ( IPC_ERR_SUCCESS != nRet )
		{
			CString str;
			str.Format( "IPC_Init called: %d !", nRet );
			AfxMessageBox( str );
		}
	}
		return bInit;
	
}



// CWebLabVideoApp::ExitInstance - DLL 终止

int CWebLabVideoApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
