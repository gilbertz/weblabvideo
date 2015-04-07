#pragma once

// WebLabVideo.h : WebLabVideo.DLL 的主头文件
#define WM_MY_MESSAGE WM_USER+0x100
#if !defined( __AFXCTL_H__ )
#error "在包括此文件之前包括“afxctl.h”"
#endif

#include "resource.h"       // 主符号


// CWebLabVideoApp : 有关实现的信息，请参阅 WebLabVideo.cpp。

class CWebLabVideoApp : public COleControlModule
{
public:
virtual	BOOL InitInstance();
virtual	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

