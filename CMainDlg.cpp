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
DWORD WINAPI ClientThread(LPVOID lpParm );
BOOL socket_Select(SOCKET hSocket,DWORD nTimeOut,BOOL bRead);
BOOL  isServerOn;

#define TIMER_ZOOM  0
#define TIMER_TICK  0
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
	isServerOn = FALSE;
	CreateThread(0,0,ClientThread,this,0,NULL);

}

CMainDlg::~CMainDlg()
{

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
	ON_MESSAGE(WM_MYMSG1,OnMyMsgHandlerShow)
	ON_MESSAGE(WM_MYMSG2,OnMyMsgHandlerPhoto)
	ON_MESSAGE(WM_MYMSG3,OnMyMsgHandlerVideo)
	ON_MESSAGE(WM_MYMSG4,OnMyMsgHandlerOperate)
	ON_MESSAGE(WM_MYMSG5,OnMyMsgHandlerNOperate)
END_MESSAGE_MAP()


DWORD WINAPI ClientThread(  LPVOID lpParameter)
{
	CMainDlg * pClient = (CMainDlg *)lpParameter;

	if(pClient->ConnectSocket(pClient))
	{

	}
	else
	{
		AfxMessageBox("socket error");  
	}
	return 0;
}


BOOL CMainDlg::ConnectSocket(CMainDlg * pClient)
{

	while (TRUE)
	{
		while (!isServerOn )
		{ 
			Sleep(1000);
			//初始化环境  
			WSADATA wd = {0};  
			int nStart = WSAStartup(MAKEWORD(SOCK_VER,0),&wd);//函数成功返回0，失败返回错误代码  
			if (0 != nStart)  
			{   //错误处理  
				//return FALSE;  
			}  

			if (2 != LOBYTE(wd.wVersion))  
			{  
				//return FALSE;  
			}  

			//创建socket套接字  
			g_sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
			if (INVALID_SOCKET == g_sock)  
			{  
				MessageBox(_T("创建socket失败"));
				//return  FALSE;  
			}  

			//绑定  
			sockaddr_in addr = {0};  
			addr.sin_family = AF_INET;  
			addr.sin_port = htons(61557);  
			addr.sin_addr.s_addr = inet_addr("202.120.37.243");  

			if (SOCKET_ERROR != connect(g_sock,(sockaddr *)&addr,sizeof(addr)))
			{
                 isServerOn =TRUE;
				 AfxMessageBox("socket 创建成功！！");  
			}
			
		}
		

		if (socket_Select(g_sock,100,TRUE))
		{
			AfxMessageBox("socket ！！");  
			char szMsg[256] = {0};
			int iRead = recv(g_sock,szMsg,256,0);
			if (iRead > 0)
			{
				AfxMessageBox(szMsg);
				//AfxMessageBox(strlen(szMsg));
				CString csMsg;
				csMsg= szMsg;
				csMsg = csMsg.Left(4);
				if (strcmp(csMsg,"show")==0)
					::PostMessage(pClient->m_hWnd,WM_MYMSG1,0,0);
				if (strcmp(csMsg,"phot")==0)
					::PostMessage(pClient->m_hWnd,WM_MYMSG2,0,0);  
				if (strcmp(csMsg,"vide")==0)
					::PostMessage(pClient->m_hWnd,WM_MYMSG3,0,0);
				if (strcmp(csMsg,"oper")==0)
					::PostMessage(pClient->m_hWnd,WM_MYMSG4,0,0);
				if (strcmp(csMsg,"nope")==0)
					::PostMessage(pClient->m_hWnd,WM_MYMSG5,0,0);
				*szMsg = '\0';
			} 
			else
			{
				AfxMessageBox(_T("已断线，请重新连接"));
				Sleep(5000);
				//return TRUE;
			}
		}
		
	}

	return TRUE;
}

BOOL socket_Select(SOCKET hSocket,DWORD nTimeOut,BOOL bRead)
{
	FD_SET fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket,&fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec = 0;
	tv.tv_usec = nTimeOut;
	int iRet = 0;
	if (bRead)
	{
		iRet = select(0,&fdset,NULL,NULL,&tv);
	} 
	else
	{
		iRet = select(0,NULL,&fdset,NULL,&tv);
	}
	if (iRet <= 0)
	{
		return FALSE;
	} 
	else if (FD_ISSET(hSocket,&fdset))
	{
		return TRUE;
	}
	return FALSE;
}

void CMainDlg::TCPSend(char szBuff[])
{   	

	int iWrite;
	iWrite = send(g_sock,szBuff,3,0);
	if(SOCKET_ERROR == iWrite){
		AfxMessageBox(_T("发送错误"));
	}
	AfxMessageBox(_T(szBuff));

	return; 

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
				TCPSend("101");

			}
			if (rect102.PtInRect(point))
			{	
				TCPSend("102");

			}
			if (rect201.PtInRect(point))
			{   
				TCPSend("201");

			}
			if (rect203.PtInRect(point))
			{   
				TCPSend("203");

			}
			if (rect204.PtInRect(point))
			{   
				TCPSend("204");

			}
			if (rect205.PtInRect(point))
			{   
				TCPSend("205");

			}
			if (rect206.PtInRect(point))
			{   
				TCPSend("206");

			}

			if (rect207.PtInRect(point))
			{   
				TCPSend("207");

			}
			if (rect208.PtInRect(point))
			{   
				TCPSend("208");

			}
			if (rect209.PtInRect(point))
			{   
				TCPSend("209");

			}
			if (rect210.PtInRect(point))
			{   
				TCPSend("210");

			}
			if (rect301.PtInRect(point))
			{   
				TCPSend("301");

			}
			if (rect401.PtInRect(point))
			{   
				TCPSend("401");

			}
			if (rect402.PtInRect(point))
			{   
				TCPSend("402");

			}
			if (rect404.PtInRect(point))
			{   

				TCPSend("404");

			}
			if (rectSTART.PtInRect(point))
			{   
				TCPSend("STA");

			}

		}
	}
	CDialog::OnLButtonUp(nFlags, point);

}

LRESULT CMainDlg::OnMyMsgHandlerShow(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("show11"); 
	// 取得播放窗口句柄
	hPlayWnd = GetDlgItem(IDC_STATIC_VIDEO)->GetSafeHwnd();

	//取得前端句柄
	int nErrcd = IPC_ERR_SUCCESS;
	//CString strIP="192.168.1.99"; 
	CString strIP="202.120.37.243";
	DWORD dwIP; 
	dwIP = inet_addr(strIP); 
	m_hHandle = IPC_Connect(dwIP, IPCSDK_VSIP_PORT, "admin", "admin", &nErrcd);// TODO: 在此添加控件通知处理程序代码

	if ( !IPC_IsRealPlay( m_hPlayer ) )
	{
		//开始播放
		int nErrCD = IPC_ERR_SUCCESS;
		m_hPlayer = IPC_RealPlay( m_hHandle, (unsigned long)hPlayWnd, &nErrCD,
			IPCSDK_RTP_PORT, PLAY_MAIN/*PLAY_SUB*/,  // PLAY_MAIN: 主流   PLAY_SUB: 辅流
			IPCSDK_MEDIA_STREAM_TYPE_UDP);           // IPCSDK_MEDIA_STREAM_TYPE_TCPSend: TCPSend传输方式


		if ( IPC_ERR_SUCCESS == nErrCD )
		{                                                                
			m_bPlayStat = true;

		}
		else
		{
			CString str;
			str.Format( "IPC_RealPlay called: %d !", nErrCD );
			AfxMessageBox( str );
		}
	}
	return 0;
}

LRESULT CMainDlg::OnMyMsgHandlerPhoto(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("photo"); 

	if( m_bPlayStat)
	{
		CString strFileName;		

		if ( LocPic(strFileName) )
		{
			AfxMessageBox( "本地抓拍成功,本地图片文件：" + strFileName );
		}
		else
		{
			AfxMessageBox( "本地抓拍失败" );
		}
	}
	else
	{
		AfxMessageBox("先播放视频，然后才能本地抓拍");
		return 0;
	}

	return 0;
}

LRESULT CMainDlg::OnMyMsgHandlerVideo(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("video"); 
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;

	if ( !m_bIsLocRec )
	{
		if( !m_bPlayStat)
		{ 
			AfxMessageBox("先播放视频，然后才能本地录像");
			return 0;
		}	
		CString strFileName;
		if (StartLocRec(strFileName) )
		{
			strTemp = "停止";

			AfxMessageBox( "本地录像开始" );
			m_bIsLocRec = TRUE;
		}
		else
		{
			AfxMessageBox( "本地录像失败" );
			m_bIsLocRec = FALSE;
		}

	}
	else
	{

		CString strFileName;
		if ( StopLocRec(strFileName) )
		{
			strTemp = "录像";


			CString strRecPath = KCSDEMO_FILEPATH; 
			strRecPath += strFileName;
			AfxMessageBox( "停止本地录像成功,本地录像文件：" + strRecPath );

			m_bIsLocRec = FALSE;
		}
		else
		{
			AfxMessageBox(  "停止本地录像失败" );
			m_bIsLocRec = TRUE;
		}
	}
	return 0;
}

LRESULT CMainDlg::OnMyMsgHandlerOperate(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("operate"); 
	int nData=1;
	ControlCamera( CAM_PRESETCALL, nData );
	IsCoperate = true ;
	return 0;
}

LRESULT CMainDlg::OnMyMsgHandlerNOperate(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox("noperate"); 
	IsCoperate = false ;
	return 0;
}

BOOL CMainDlg::LocPic(CString &strFileName)
{
	CTime t = CTime::GetCurrentTime();
	m_strPicFileName = KCSDEMO_FILEPATH + t.Format( "KCSDEMO-%Y%m%d%H%M%S.bmp" );
	strFileName = m_strPicFileName;
	int nRet = IPC_LocalSnapshot( m_hPlayer, (LPCTSTR)strFileName, IPCSDK_PIC_ENC_JPEG );
	if ( IPC_ERR_SUCCESS != nRet )
	{
		CString str;
		str.Format( "IPC_LocalSnapshot called: %d !", nRet );
		AfxMessageBox( str );

		return false;
	}
	Sleep(1000); // Sleep() must be put at the end !!!

	return true;
}

BOOL CMainDlg::StartLocRec(CString &strFileName)
{
	CTime t = CTime::GetCurrentTime();
	m_strRecFileName = t.Format( "%Y%m%d-%H%M%S" );
	m_strRecFileName += ".asf";
	strFileName = m_strRecFileName;

	int nRet = IPC_StartLocalRec( m_hHandle, m_hPlayer, (LPCTSTR)m_strRecFileName, KCSDEMO_FILEPATH, 
		IPCSDK_LOCAL_REC_PORT, fPuLocRecStateCB, this );
	if ( IPC_ERR_SUCCESS == nRet )
	{
		Sleep(1000); // Sleep() must be put at the end !!!
	}
	else
	{
		CString str;
		str.Format( "IPC_StartLocalRec called: %d !", nRet );
		AfxMessageBox( str );
	}

	return IsLocRec();
}

BOOL CMainDlg::StopLocRec(CString &strFileName)
{
	strFileName = m_strRecFileName;

	if ( IsLocRec() )
	{
		int nRet = IPC_StopLocalRec( m_hPlayer, TRUE );
		if ( IPC_ERR_SUCCESS != nRet )
		{
			CString str;
			str.Format( "IPC_StopLocalRec called: %d !", nRet );
			AfxMessageBox( str );
		}
	}

	return ( !IsLocRec() );
}

BOOL CMainDlg::IsLocRec() 
{
	return IPC_IsLocalRecording( m_hPlayer );
}