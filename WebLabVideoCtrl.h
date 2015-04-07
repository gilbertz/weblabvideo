#pragma once

// WebLabVideoCtrl.h : CWebLabVideoCtrl ActiveX 控件类的声明。


// CWebLabVideoCtrl : 有关实现的信息，请参阅 WebLabVideoCtrl.cpp。


#include "CMainDlg.h"
class CWebLabVideoCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebLabVideoCtrl)

// 构造函数
public:
	CWebLabVideoCtrl();

// 重写
public:
//	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// 实现
protected:
	~CWebLabVideoCtrl();

	BEGIN_OLEFACTORY(CWebLabVideoCtrl)        // 类工厂和 guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CWebLabVideoCtrl)

	DECLARE_OLETYPELIB(CWebLabVideoCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebLabVideoCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CWebLabVideoCtrl)		// 类型名称和杂项状态

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID


public:
        CMainDlg m_ctrldlg;

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);

};

