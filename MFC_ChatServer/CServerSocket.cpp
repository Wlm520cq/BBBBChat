#include "pch.h"
#include "CServerSocket.h"
#include "MFC_ChatServer.h"
#include "MFC_ChatServerDlg.h"

CServerSocket::CServerSocket()
{

}

CServerSocket::~CServerSocket()
{

}

//重写：特殊用途->有谁连接到服务端   显示信息
void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("####OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	dlg->m_chat = new CChatSocket;
	//开始接受连接
	Accept(*(dlg->m_chat));

#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("客服端连接成功！");
#endif

	CString strShow;
	CString strInfo = _T("客服端连接成功！");
	strShow =dlg->CatShowString(strInfo, _T(" "));

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(false);

	CAsyncSocket::OnAccept(nErrorCode);
}
