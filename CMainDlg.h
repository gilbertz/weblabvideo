
#define WM_MYMSG WM_USER+100


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
	afx_msg LRESULT OnMyMsgHandler(WPARAM wParam, LPARAM lParam);

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