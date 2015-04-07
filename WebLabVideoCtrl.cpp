// WebLabVideoCtrl.cpp : CWebLabVideoCtrl ActiveX 控件类的实现。

#include "stdafx.h"
#include "WebLabVideo.h"
#include "WebLabVideoCtrl.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CWebLabVideoCtrl, COleControl)



	// 消息映射

	BEGIN_MESSAGE_MAP(CWebLabVideoCtrl, COleControl)
		ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_WM_RBUTTONDOWN()
	END_MESSAGE_MAP()



	// 调度映射

	BEGIN_DISPATCH_MAP(CWebLabVideoCtrl, COleControl)
		DISP_FUNCTION_ID(CWebLabVideoCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	END_DISPATCH_MAP()



	// 事件映射

	BEGIN_EVENT_MAP(CWebLabVideoCtrl, COleControl)

	END_EVENT_MAP()



	// 属性页

	// TODO: 按需要添加更多属性页。请记住增加计数!
	BEGIN_PROPPAGEIDS(CWebLabVideoCtrl, 1)

	END_PROPPAGEIDS(CWebLabVideoCtrl)



	// 初始化类工厂和 guid

	IMPLEMENT_OLECREATE_EX(CWebLabVideoCtrl, "WEBLABVIDEO.WebLabVideoCtrl.1",
		0x1255c724, 0x2d2e, 0x4fdf, 0x91, 0x38, 0xa7, 0x83, 0x30, 0xc4, 0x9b, 0xd1)



		// 键入库 ID 和版本

		IMPLEMENT_OLETYPELIB(CWebLabVideoCtrl, _tlid, _wVerMajor, _wVerMinor)



		// 接口 ID

		const IID IID_DWebLabVideo = { 0x29D4B94A, 0xA38F, 0x4EE5, { 0xB4, 0x88, 0x77, 0x3C, 0x7B, 0x93, 0x32, 0x5C } };
	const IID IID_DWebLabVideoEvents = { 0xDC1DA45A, 0x7801, 0x48C9, { 0x8E, 0x67, 0xE6, 0x15, 0xCF, 0xC4, 0x2, 0xB1 } };


	// 控件类型信息

	static const DWORD _dwWebLabVideoOleMisc =
		OLEMISC_ACTIVATEWHENVISIBLE |
		OLEMISC_SETCLIENTSITEFIRST |
		OLEMISC_INSIDEOUT |
		OLEMISC_CANTLINKINSIDE |
		OLEMISC_RECOMPOSEONRESIZE;

	IMPLEMENT_OLECTLTYPE(CWebLabVideoCtrl, IDS_WEBLABVIDEO, _dwWebLabVideoOleMisc)



		// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::UpdateRegistry -
		// 添加或移除 CWebLabVideoCtrl 的系统注册表项

		BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::UpdateRegistry(BOOL bRegister)
	{
		// TODO: 验证您的控件是否符合单元模型线程处理规则。
		// 有关更多信息，请参考 MFC 技术说明 64。
		// 如果您的控件不符合单元模型规则，则
		// 必须修改如下代码，将第六个参数从
		// afxRegApartmentThreading 改为 0。

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



	// 授权字符串

	static const TCHAR _szLicFileName[] = _T("WebLabVideo.lic");

	static const WCHAR _szLicString[] = L"Copyright (c) 2014 ";



	// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::VerifyUserLicense -
	// 检查是否存在用户许可证

	BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::VerifyUserLicense()
	{
		return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
			_szLicString);
	}



	// CWebLabVideoCtrl::CWebLabVideoCtrlFactory::GetLicenseKey -
	// 返回运行时授权密钥

	BOOL CWebLabVideoCtrl::CWebLabVideoCtrlFactory::GetLicenseKey(DWORD dwReserved,
		BSTR *pbstrKey)
	{
		if (pbstrKey == NULL)
			return FALSE;

		*pbstrKey = SysAllocString(_szLicString);
		return (*pbstrKey != NULL);
	}



	// CWebLabVideoCtrl::CWebLabVideoCtrl - 构造函数

	CWebLabVideoCtrl::CWebLabVideoCtrl()
	{
		InitializeIIDs(&IID_DWebLabVideo, &IID_DWebLabVideoEvents);
		// TODO: 在此初始化控件的实例数据。
	}



	// CWebLabVideoCtrl::~CWebLabVideoCtrl - 析构函数

	CWebLabVideoCtrl::~CWebLabVideoCtrl()
	{
		// TODO: 在此清理控件的实例数据。

	}



	// CWebLabVideoCtrl::OnDraw - 绘图函数

	//void CWebLabVideoCtrl::OnDraw(
	//			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
	//{
	//	if (!pdc)
	//		return;
	//
	//	// TODO: 用您自己的绘图代码替换下面的代码。
	//	/*pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	//	pdc->Ellipse(rcBounds);*/
	//}



	// CWebLabVideoCtrl::DoPropExchange - 持久性支持

	void CWebLabVideoCtrl::DoPropExchange(CPropExchange* pPX)
	{
		ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
		COleControl::DoPropExchange(pPX);

		// TODO: 为每个持久的自定义属性调用 PX_ 函数。
	}



	// CWebLabVideoCtrl::OnResetState - 将控件重置为默认状态

	void CWebLabVideoCtrl::OnResetState()
	{
		COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值

		// TODO: 在此重置任意其他控件状态。
	}



	// CWebLabVideoCtrl::AboutBox - 向用户显示“关于”框

	void CWebLabVideoCtrl::AboutBox()
	{
		CDialogEx dlgAbout(IDD_ABOUTBOX_WEBLABVIDEO);
		dlgAbout.DoModal();
	}



	// CWebLabVideoCtrl 消息处理程序

	int CWebLabVideoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{

		// TODO:  在此添加您专用的创建代码
		if (COleControl::OnCreate(lpCreateStruct) == -1)
			return -1;
		m_ctrldlg.Create(IDD_MAIN_DIALOG,this);


		return 0;
	}


	void CWebLabVideoCtrl::OnSize(UINT nType, int cx, int cy)
	{

		// TODO: 在此处添加消息处理程序代码
		COleControl::OnSize(nType, cx, cy);
		RECT activeXRect;
		GetClientRect(&activeXRect);
		m_ctrldlg.MoveWindow (&activeXRect);
	}

