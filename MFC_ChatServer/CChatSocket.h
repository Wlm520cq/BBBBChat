#pragma once
#include <afxsock.h>
/*
	�����ࣺ��ͷ���ͨ�ŵ�
*/
class CChatSocket :
	public CAsyncSocket
{
public:
	CChatSocket();
	virtual ~CChatSocket();
	virtual void OnReceive(int nErrorCode);
};

