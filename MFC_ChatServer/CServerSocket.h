#pragma once
#include <afxsock.h>

/*
	�����ࣺΪ�����ͷ��˵����ж���
*/
class CServerSocket :
	public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);

};

