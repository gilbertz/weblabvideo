#pragma once

// WebLabVideo.h : WebLabVideo.DLL ����ͷ�ļ�
#define WM_MY_MESSAGE WM_USER+0x100
#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������


// CWebLabVideoApp : �й�ʵ�ֵ���Ϣ������� WebLabVideo.cpp��

class CWebLabVideoApp : public COleControlModule
{
public:
virtual	BOOL InitInstance();
virtual	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

