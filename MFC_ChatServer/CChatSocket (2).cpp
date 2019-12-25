#include "pch.h"
#include "CChatSocket.h"
#include "MFC_ChatServerDlg.h"
#include "MFC_ChatServer.h"

CChatSocket::CChatSocket()
{

}

CChatSocket::~CChatSocket()
{

}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1. 接受数据到 szRecvBuf
	TRACE("#### Server OnReceive");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	char szRecvBuf[SEND_SERVER_BUF] = { 0 };
	Receive(szRecvBuf, SEND_SERVER_BUF, 0);
	TRACE("#### Server szRecv=%d", szRecvBuf);

	//2.显示 szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3.显示到列表框
	CString strShow;
	CString strInfo = _T(" ");
	strShow =dlg->CatShowString(strInfo, strRecvMsg);

#if 0
	CString strShow = _T("客户端: ");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");
	strShow = strTime + strShow; //时间 + 我：内容
	strShow += strRecvMsg;
#endif

	dlg->m_list.AddString(strShow);

	CAsyncSocket::OnReceive(nErrorCode);
}
