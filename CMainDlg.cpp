// CMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WebLabVideo.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <WINSOCK.H>//套接字所需的头文件

#pragma comment(lib,"WSOCK32.LIB")//windows套接字的库文件

#define SOCK_VER 2 //程序使用的winsock主版本

//变量和函数的声明
SOCKET g_sock = 0; //套接字声明
void ErrMsg(DWORD dwErr);//错误信息打印
UINT  ServerRecvThread(LPVOID lpParm );
sockaddr_in addr = {0};

#define TIMER_ZOOM  0
#define KCSDEMO_FILEPATH  "C:\\"
// 前端句柄
#define PUHANDLE        unsigned long
// 播放器句柄
#define PLAYERHANDLE    unsigned long
/*
*录像状态回调函数, 对应的回调类型和结构如上所示	
*/
void __stdcall fPuLocRecStateCB( PUHANDLE hHandle, PLAYERHANDLE hPlayHandle, unsigned long dwRecorderID, unsigned long dwCBType,
	void* pData, int nDataLen, void* pContext )									
{
	TRACE( "Demo [LocRecState] pu:%d, ply:%d, type:%d, data:0x%08x, len:%d, param:0x%08x !\n", 
		hHandle, hPlayHandle, dwCBType, pData, nDataLen, pContext );
}

// CMainDlg 对话框
IMPLEMENT_DYNAMIC(CMainDlg, CDialog)
	CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
	m_hPlayer = NULL;
	m_hHandle = NULL;
	m_byRange = 10;
	activex=GetParent();
	m_bFullScreen = false;
	Audio=false;
	IsMove=false;
	IsCoperate=false;
	m_bPlayStat=false;
	m_bIsLocRec=false;
	wPort = 0;
	byADecChn = 0;
	bMute=1;
	IsCoperate=true;

	

}

CMainDlg::~CMainDlg()
{
	//关闭资源  
    closesocket(g_sock);//关闭套接字 

	WSACleanup();//清理环境  
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{

}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)

	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_MESSAGE(WM_MYMSG,OnMyMsgHandler)
END_MESSAGE_MAP()

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();  

	 //初始化环境  
    WSADATA wd = {0};  
    WSAStartup(MAKEWORD(SOCK_VER,0),&wd);
  

    //创建socket套接字  
    socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);  

    MessageBox("socket 创建成功！！");  

	addr.sin_family = AF_INET;//IPV4
	addr.sin_port = htons(61557);//端口
	addr.sin_addr.s_addr = inet_addr("202.120.37.243");//IP
	int nBind = bind(g_sock,(sockaddr *)&addr,sizeof(addr));//成功返回0

	    //获得已经绑定的端口号  
    int nLen = sizeof(addr);  
    getsockname(g_sock,(sockaddr *)&addr,&nLen);  

	CString str;
	str.Format( "socket 成功绑定到端口：%d,等待数据。。。", ntohs(addr.sin_port) );
	AfxMessageBox( str ); 

	 m_bTerminateThread = false; 
	 AfxBeginThread(ServerRecvThread, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);  
	 return TRUE; 
}

UINT  ServerRecvThread(LPVOID lpParm )
{
    CString str;
    //等待并接收数据  
    sockaddr_in saClient = {0};                                 
    int nFromLen = sizeof(saClient);  
    char szBuff[256]={0};
	CString  m_str(szBuff);  
	str.Format( szBuff );
	AfxMessageBox( str ); 
    recvfrom(g_sock,szBuff,256,0,(sockaddr *)&saClient,&nFromLen);  

	str.Format( "收到的信息：%s,从%s,%d ",szBuff,inet_ntoa(saClient.sin_addr),ntohs(saClient.sin_port) );
	AfxMessageBox( str ); 

	if (strcmp(szBuff,"")==0)
	{
			AfxMessageBox( "aaaaaaaa" );
		::SendMessage(AfxGetMainWnd()->m_hWnd,WM_MYMSG,(WPARAM)szBuff,0);
	}

	return 0;  

}
void CMainDlg::UDP(char szBuff[])
{   
	//发送数据包
	int nSent = sendto(g_sock,szBuff,strlen(szBuff)+1,0,(sockaddr * )&addr,sizeof(addr));
}

//打印错误信息函数
void ErrMsg(DWORD dwErr)
{
	char szErr[1024] = {0};
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,dwErr,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),(LPSTR)szErr,1024,NULL);
	printf(szErr);
}

void CMainDlg::ControlCamera( ECamControl eType, BYTE byData )
{
	TIPC_VIDEO_ENC_INPUT_PT_PARAM tInfo = {0};
	int nRet = IPC_GetPuParam( m_hHandle, IPCSDK_PARAM_VIDEO_ENC_INPUTPORT, &tInfo, sizeof(tInfo) );
	if ( IPC_ERR_SUCCESS != nRet )
	{
		CString str;
		str.Format( "IPC_GetPuParam called: %d !", nRet );
		AfxMessageBox( str );
		return ;
	}
	nRet = IPC_PTZControl( m_hHandle, tInfo.byVideoInputPort, eType, &byData );
	if ( IPC_ERR_SUCCESS != nRet )
	{
		CString str;
		str.Format( "IPC_PTZControl called: %d !", nRet );
		AfxMessageBox( str );
	}	
}


/*滚轮操作视频放大缩小*/
BOOL CMainDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{   
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!IsCoperate)
	{
		if(IsPtInRect(pt))
		{

			SetTimer(TIMER_ZOOM, 500, NULL);
			if(zDelta < 0)
			{ 
				ControlCamera(  (ECamControl)CAM_ZOOMWIDE, (BYTE)m_byRange );
			}
			else if (zDelta > 0)
			{  
				ControlCamera(  (ECamControl)CAM_ZOOMTELE, (BYTE)m_byRange );
			}
		}
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

/*放大缩小定时器*/
void CMainDlg::OnTimer(UINT nIDEvent)
{
	if (TIMER_ZOOM == nIDEvent )
	{
		ControlCamera(  (ECamControl)CAM_ZOOMSTOP, (BYTE)m_byRange );

		KillTimer(TIMER_ZOOM);
	}
}

void CMainDlg::OnMouseMove(UINT nFlags, CPoint point)
{   

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!IsCoperate)
	{
		if (nFlags == MK_LBUTTON&&IsPtInRect(point))
		{
			HCURSOR hCursor;
			hCursor = ::LoadCursor(NULL,IDC_HAND);
			SetCursor(hCursor);
			IsMove=true;
			m_move=m_start;
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CMainDlg::IsPtInRect(CPoint point)
{   
	CRect rect;
	GetDlgItem(IDC_STATIC_VIDEO)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	return rect.PtInRect(point);   
}

void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值	
	if(!IsCoperate)
	{
		m_start = point;	
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CMainDlg::OnLButtonUp(UINT nFlags, CPoint point)
{   
	// 获得父窗口的句柄
	if(!IsCoperate)
	{
		if(IsMove)
		{   
			IsMove=false;
			char chX = (char)m_move.x ;
			char chY = (char)m_move.y ;

			IPC_PTZControlEx(m_hHandle,0,CAM_GOTOPT,chX,chY);
		}
	}
	else
	{
		HWND hWnd = this->GetParent()->GetSafeHwnd();  

		// 向父窗口发送消息  
		if (hWnd == NULL) return (void)MessageBox(_T("获得父窗口句柄失败！"));  

		// 定义发送的文本  
		CString strSend= _T("");  

		CRect rectSTART(75,125,85,135);
		CRect rect101(286,230,296,240);
		CRect rect102(287,263,297,273);
		CRect rect201(355,145,365,155);
		CRect rect203(389,113,399,123);
		CRect rect204(544,116,554,126);
		CRect rect205(470,164,490,174);
		CRect rect206(663,232,673,242);
		CRect rect207(714,167,724,177);
		CRect rect208(717,200,727,210);
		CRect rect209(989,150,999,160);
		CRect rect210(987,187,997,197);
		CRect rect301(627,382,637,392);
		CRect rect401(660,348,670,358);
		CRect rect402(778,349,788,359);
		CRect rect404(813,349,823,359);

		if(!m_bFullScreen)
		{
			if (rect101.PtInRect(point))
			{   
				UDP("101");

			}
			if (rect102.PtInRect(point))
			{	
				UDP("102");

			}
			if (rect201.PtInRect(point))
			{   
				UDP("201");

			}
			if (rect203.PtInRect(point))
			{   
				UDP("203");

			}
			if (rect204.PtInRect(point))
			{   
				UDP("204");

			}
			if (rect205.PtInRect(point))
			{   
				UDP("205");

			}
			if (rect206.PtInRect(point))
			{   
				UDP("206");

			}

			if (rect207.PtInRect(point))
			{   
				UDP("207");

			}
			if (rect208.PtInRect(point))
			{   
				UDP("208");

			}
			if (rect209.PtInRect(point))
			{   
				UDP("209");

			}
			if (rect210.PtInRect(point))
			{   
				UDP("210");

			}
			if (rect301.PtInRect(point))
			{   
				UDP("301");

			}
			if (rect401.PtInRect(point))
			{   
				UDP("401");

			}
			if (rect402.PtInRect(point))
			{   
				UDP("402");

			}
			if (rect404.PtInRect(point))
			{   

				UDP("404");

			}
			if (rectSTART.PtInRect(point))
			{   
				UDP("START");

			}
			else
			{
			}
			// ::SendNotifyMessage(hWnd,WM_MY_MESSAGE,(WPARAM)&strSend,NULL);

		}
	}
	CDialog::OnLButtonUp(nFlags, point);

}


//BOOL CMainDlg::LocPic(CString &strFileName)
//{
//	CTime t = CTime::GetCurrentTime();
//	m_strPicFileName = KCSDEMO_FILEPATH + t.Format( "KCSDEMO-%Y%m%d%H%M%S.bmp" );
//	strFileName = m_strPicFileName;
//	int nRet = IPC_LocalSnapshot( m_hPlayer, (LPCTSTR)strFileName, IPCSDK_PIC_ENC_JPEG );
//	if ( IPC_ERR_SUCCESS != nRet )
//	{
//		CString str;
//		str.Format( "IPC_LocalSnapshot called: %d !", nRet );
//		AfxMessageBox( str );
//
//		return false;
//	}
//	Sleep(1000); // Sleep() must be put at the end !!!
//
//	return true;
//}
//
//void CMainDlg::OnBnClickedButtonPhoto()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	if( m_bPlayStat)
//	{
//		CString strFileName;		
//
//		if ( LocPic(strFileName) )
//		{
//			AfxMessageBox( "本地抓拍成功,本地图片文件：" + strFileName );
//		}
//		else
//		{
//			AfxMessageBox( "本地抓拍失败" );
//		}
//	}
//	else
//	{
//		AfxMessageBox("先播放视频，然后才能本地抓拍");
//		return;
//	}
//
//}
//
//BOOL CMainDlg::StartLocRec(CString &strFileName)
//{
//	CTime t = CTime::GetCurrentTime();
//	m_strRecFileName = t.Format( "%Y%m%d-%H%M%S" );
//	m_strRecFileName += ".asf";
//	strFileName = m_strRecFileName;
//
//	int nRet = IPC_StartLocalRec( m_hHandle, m_hPlayer, (LPCTSTR)m_strRecFileName, KCSDEMO_FILEPATH, 
//		IPCSDK_LOCAL_REC_PORT, fPuLocRecStateCB, this );
//	if ( IPC_ERR_SUCCESS == nRet )
//	{
//		Sleep(1000); // Sleep() must be put at the end !!!
//	}
//	else
//	{
//		CString str;
//		str.Format( "IPC_StartLocalRec called: %d !", nRet );
//		AfxMessageBox( str );
//	}
//
//	return IsLocRec();
//}
//
//BOOL CMainDlg::StopLocRec(CString &strFileName)
//{
//	strFileName = m_strRecFileName;
//
//	if ( IsLocRec() )
//	{
//		int nRet = IPC_StopLocalRec( m_hPlayer, TRUE );
//		if ( IPC_ERR_SUCCESS != nRet )
//		{
//			CString str;
//			str.Format( "IPC_StopLocalRec called: %d !", nRet );
//			AfxMessageBox( str );
//		}
//	}
//
//	return ( !IsLocRec() );
//}
//
//BOOL CMainDlg::IsLocRec() 
//{
//	return IPC_IsLocalRecording( m_hPlayer );
//}
//
//void CMainDlg::OnBnClickedButtonRecord()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString strTemp;
//	GetDlgItemText( IDC_BUTTON_RECORD, strTemp );
//	if ( !m_bIsLocRec )
//	{
//		if( !m_bPlayStat)
//		{ 
//			AfxMessageBox("先播放视频，然后才能本地录像");
//			return;
//		}	
//		CString strFileName;
//		if (StartLocRec(strFileName) )
//		{
//			strTemp = "停止";
//			SetDlgItemText( IDC_BUTTON_RECORD, strTemp );
//			AfxMessageBox( "本地录像开始" );
//			m_bIsLocRec = TRUE;
//		}
//		else
//		{
//			AfxMessageBox( "本地录像失败" );
//			m_bIsLocRec = FALSE;
//		}
//
//	}
//	else
//	{
//
//		CString strFileName;
//		if ( StopLocRec(strFileName) )
//		{
//			strTemp = "录像";
//			SetDlgItemText(IDC_BUTTON_RECORD, strTemp );
//
//			CString strRecPath = KCSDEMO_FILEPATH; 
//			strRecPath += strFileName;
//			AfxMessageBox( "停止本地录像成功,本地录像文件：" + strRecPath );
//
//			m_bIsLocRec = FALSE;
//		}
//		else
//		{
//			AfxMessageBox(  "停止本地录像失败" );
//			m_bIsLocRec = TRUE;
//		}
//	}
//
//}

LRESULT CMainDlg::OnMyMsgHandler(WPARAM wParam, LPARAM lParam)
{
	CString str;
	char *pStr0= (char *)wParam; 
	str.Format(_T("%S"),pStr0);
	AfxMessageBox("HAHHA");
	AfxMessageBox(str);
	return 0;
}
