// WebLabVideoCtrl.cpp : CWebLabVideoCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "WebLabVideo.h"
#include "WebLabVideoCtrl.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CWebLabVideoCtrl, COleControl)



	// ��Ϣӳ��

	BEGIN_MESSAGE_MAP(CWebLabVideoCtrl, COleControl)
		ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()



	// ����ӳ��

	BEGIN_DISPATCH_MAP(CWebLabVideoCtrl, COleControl)
		DISP_FUNCTION_ID(CWebLabVideoCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	END_DISPATCH_MAP()



	// �¼�ӳ��

	BEGIN_EVENT_MAP(CWebLabVideoCtrl, COleControl)

	END_EVENT_MAP()



	// ����ҳ

	// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
	BEGIN_PROPPAGEIDS(CWebLabVideoCtrl, 1)

	END_PROPPAGEIDS(CWebLabVideoCtrl)



	// ��ʼ���๤���� guid

	IMPLEMENT_OLECREATE_EX(CWebLabVideoCtrl, "WEBLABVIDEO.WebLabVideoCtrl.1",
		0x1255c724, 0x2d2e, 0x4fdf, 0x91, 0x38, 0xa7, 0x83, 0x30, 0xc4, 0x9b, 0xd1)



		// ����� ID �Ͱ汾

		IMPLEMENT_OLETYPELIB(CWebLabVideoCtrl, _tlid, _wVerMajor, _wVerMinor)



		// �ӿ� ID

		const IID IID_DWebLabVideo = { 0x29D4B94A, 0xA38F, 0x4EE5, { 0xB4, 0x88, 0x77, 0x3C, 0x7B, 0x93, 0x32, 0x5C } };
	const IID IID_DWebLabVideoEvents = { 0xDC1DA45A, 0x7801, 0x48C9, { 0x8E, 0x67, 0xE6, 0x15, 0xCF, 0xC4, 0x2, 0xB1 } };


	// �ؼ�������Ϣ

	static const DWORD _dwWebLabVideoOleMisc =
		OLEMISC_ACTIVATEWHENVISIBLE |
		OLEMISC_SETCLIENTSITEFIRST |
		OLEMISC_INSIDEOUT |
		OLEMISC_CANTLINKINSIDE |
		OLEMISC_RECOMPOSEONRESIZE;

	IMPLEMENT_OLECTLTYPE(CWebLabVideoCtrl, IDS_WEBLABVIDEO, _dwWebLabVideoOleMisc)



		// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::UpdateRegistry -
		// ��ӻ��Ƴ� CWebLabVideoCtrl ��ϵͳע�����

		BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::UpdateRegistry(BOOL bRegister)
	{
		// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
		// �йظ�����Ϣ����ο� MFC ����˵�� 64��
		// ������Ŀؼ������ϵ�Ԫģ�͹�����
		// �����޸����´��룬��������������
		// afxRegApartmentThreading ��Ϊ 0��

		if (bRegister)
			return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_WEBLABVIDEO,
			IDB_WEBLABVIDEO,
			afxRegApartmentThreading,
			_dwWebLabVideoOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
		else
			return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
	}



	// ��Ȩ�ַ���

	static const TCHAR _szLicFileName[] = _T("WebLabVideo.lic");

	static const WCHAR _szLicString[] = L"Copyright (c) 2014 ";



	// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::VerifyUserLicense -
	// ����Ƿ�����û����֤

	BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::VerifyUserLicense()
	{
		return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
			_szLicString);
	}



	// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::GetLicenseKey -
	// ��������ʱ��Ȩ��Կ

	BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::GetLicenseKey(DWORD dwReserved,
		BSTR *pbstrKey)
	{
		if (pbstrKey == NULL)
			return FALSE;

		*pbstrKey = SysAllocString(_szLicString);
		return (*pbstrKey != NULL);
	}



	// CWebLabVideoCtrl::CWebLabVideoCtrl - ���캯��

	CWebLabVideoCtrl::CWebLabVideoCtrl()
	{
		InitializeIIDs(&IID_DWebLabVideo, &IID_DWebLabVideoEvents);
		// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
	}



	// CWebLabVideoCtrl::~CWebLabVideoCtrl - ��������

	CWebLabVideoCtrl::~CWebLabVideoCtrl()
	{
		// TODO: �ڴ�����ؼ���ʵ�����ݡ�

	}



	// CWebLabVideoCtrl::OnDraw - ��ͼ����

	//void CWebLabVideoCtrl::OnDraw(
	//			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
	//{
	//	if (!pdc)
	//		return;
	//
	//	// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	//	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//	pdc->Ellipse(rcBounds);*/
	//}



	// CWebLabVideoCtrl::DoPropExchange - �־���֧��

	void CWebLabVideoCtrl::DoPropExchange(CPropExchange* pPX)
	{
		ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
		COleControl::DoPropExchange(pPX);

		// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
	}



	// CWebLabVideoCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

	void CWebLabVideoCtrl::OnResetState()
	{
		COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

		// TODO: �ڴ��������������ؼ�״̬��
	}



	// CWebLabVideoCtrl::AboutBox - ���û���ʾ�����ڡ���

	void CWebLabVideoCtrl::AboutBox()
	{
		CDialogEx dlgAbout(IDD_ABOUTBOX_WEBLABVIDEO);
		dlgAbout.DoModal();
	}



	// CWebLabVideoCtrl ��Ϣ�������

	int CWebLabVideoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		// TODO:  �ڴ������ר�õĴ�������
		if (COleControl::OnCreate(lpCreateStruct) == -1)
			return -1;
		m_ctrldlg.Create(IDD_MAIN_DIALOG,this);


		return 0;
	}


	void CWebLabVideoCtrl::OnSize(UINT nType, int cx, int cy)
	{

		// TODO: �ڴ˴������Ϣ����������
		COleControl::OnSize(nType, cx, cy);
		RECT activeXRect;
		GetClientRect(&activeXRect);
		m_ctrldlg.MoveWindow (&activeXRect);
	}

