
#define WM_MYMSG1 WM_USER+101
#define WM_MYMSG2 WM_USER+102
#define WM_MYMSG3 WM_USER+103
#define WM_MYMSG4 WM_USER+104
#define WM_MYMSG5 WM_USER+105

// CMainDlg �Ի���
class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

	// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };
	//���������
	void ControlCamera( ECamControl eType, BYTE byData );
	//ȷ�����Ƿ�����Ƶ����
	BOOL CMainDlg::IsPtInRect(CPoint point);
	void CMainDlg::UDP(char szBuff[]);

	CPoint m_start;
	CPoint m_move;
	CString m_strPicFileName;
	CString m_strRecFileName;
	CComboBox m_cPos;

	// ��ص���ƶ���ָ��
    HWND hPlayWnd;
	unsigned long m_hHandle;
	unsigned long m_hPlayer;
	int wPort;
	int byADecChn;
	BYTE m_byRange;
	CWnd* activex;
	bool m_bPlayStat;

	// ��Ϊtrue����ֹ�߳�  
    bool m_bTerminateThread; 

	void CMainDlg::OnTimer(UINT nIDEvent);

	BOOL CMainDlg::LocPic(CString &strFileName);

	BOOL CMainDlg::StartLocRec(CString &strFileName);

	BOOL CMainDlg::StopLocRec(CString &strFileName);

	BOOL CMainDlg::IsLocRec() ;
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();  

	afx_msg LRESULT OnMyMsgHandlerShow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerPhoto(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerVideo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMyMsgHandlerNOperate(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	unsigned long m_handleDec;       // ���������
	WINDOWPLACEMENT _tempdlg;        // ȫ��ʱ����ԭ������Ϣ,�����ָ�����  window's placement
	WINDOWPLACEMENT _tempvid;        // ȫ��ʱ����ԭ������Ϣ,�����ָ�����  window's placement
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