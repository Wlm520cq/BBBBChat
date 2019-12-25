#pragma once
#include <afxsock.h>

/*
	服务类：为监听客服端的所有动作
*/
class CServerSocket :
	public CAsyncSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);

};

