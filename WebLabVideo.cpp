// WebLabVideo.cpp : CWebLabVideoApp �� DLL ע���ʵ�֡�

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



// CWebLabVideoApp::InitInstance - DLL ��ʼ��

BOOL CWebLabVideoApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{	
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣

		/* ��ʼ��IPCSDK */
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



// CWebLabVideoApp::ExitInstance - DLL ��ֹ

int CWebLabVideoApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
