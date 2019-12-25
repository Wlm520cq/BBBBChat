#pragma once
#include <afxsock.h>
/*
	聊天类：与客服端通信的
*/
class CChatSocket :
	public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();
	virtual void OnReceive(int nErrorCode);
};

