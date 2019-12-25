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

//��д��������;->��˭���ӵ������   ��ʾ��Ϣ
void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("####OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();

	dlg->m_chat = new CChatSocket;
	//��ʼ��������
	Accept(*(dlg->m_chat));

#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += _T("�ͷ������ӳɹ���");
#endif

	CString strShow;
	CString strInfo = _T("�ͷ������ӳɹ���");
	strShow =dlg->CatShowString(strInfo, _T(" "));

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(false);

	CAsyncSocket::OnAccept(nErrorCode);
}
