#pragma once

// WebLabVideoCtrl.h : CWebLabVideoCtrl ActiveX �ؼ����������


// CWebLabVideoCtrl : �й�ʵ�ֵ���Ϣ������� WebLabVideoCtrl.cpp��


#include "CMainDlg.h"
class CWebLabVideoCtrl : public COleControl
{
	DECLARE_DYNCREATE(CWebLabVideoCtrl)

// ���캯��
public:
	CWebLabVideoCtrl();

// ��д
public:
//	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();

// ʵ��
protected:
	~CWebLabVideoCtrl();

	BEGIN_OLEFACTORY(CWebLabVideoCtrl)        // �๤���� guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CWebLabVideoCtrl)

	DECLARE_OLETYPELIB(CWebLabVideoCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CWebLabVideoCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CWebLabVideoCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID


public:
        CMainDlg m_ctrldlg;

		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);

};

