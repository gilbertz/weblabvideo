
#define WM_MYMSG1 WM_USER+101
#define WM_MYMSG2 WM_USER+102
#define WM_MYMSG3 WM_USER+103
#define WM_MYMSG4 WM_USER+104
#define WM_MYMSG5 WM_USER+105

// CMainDlg 对话框
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

	// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };
	//控制摄像机
	void ControlCamera( ECamControl eType, BYTE byData );
	//确定点是否在视频界面
	BOOL CMainDlg::IsPtInRect(CPoint point);
	void CMainDlg::TCPSend(char szBuff[]);

	CPoint m_start;
	CPoint m_move;
	CString m_strPicFileName;
	CString m_strRecFileName;
	CComboBox m_cPos;

	// 监控点控制对象指针
    HWND hPlayWnd;
	unsigned long m_hHandle;
	unsigned long m_hPlayer;
	int wPort;
	int byADecChn;
	BYTE m_byRange;
	CWnd* activex;
	bool m_bPlayStat;

	// 若为true则终止线程  
    bool m_bTerminateThread; 
	BOOL ConnectSocket(CMainDlg * pClient);

	void CMainDlg::OnTimer(UINT nIDEvent);

	BOOL CMainDlg::LocPic(CString &strFileName);

	BOOL CMainDlg::StartLocRec(CString &strFileName);

	BOOL CMainDlg::StopLocRec(CString &strFileName);

	BOOL CMainDlg::IsLocRec() ;
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
 

	afx_msg LRESULT OnMyMsgHandlerShow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerPhoto(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerVideo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerNOperate(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	unsigned long m_handleDec;       // 解码器句柄
	WINDOWPLACEMENT _tempdlg;        // 全屏时保存原窗口信息,用来恢复窗口  window's placement
	WINDOWPLACEMENT _tempvid;        // 全屏时保存原窗口信息,用来恢复窗口  window's placement
	bool m_bFullScreen;
	bool IsMove;
	bool IsCoperate;
	int bMute;
	bool Audio;
	bool m_bIsLocRec;
	HWND m_hWndParent;
	
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};