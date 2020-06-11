#pragma once

#include "net/Socket.h"
#include "Message.h"
#include "GlObject.h"
#include "CaptureOption.h"

class Messenger
{
public:
	Messenger();
	Messenger(Socket socket);
	int send(Message& msg);
	int send(GlObject& obj);

	int sendRequestFinish();
	int sendRequestError(const char* error = NULL);
	
	int sendTexUnits(int num, u8 curActiveTexUnit, u32* texIds_2D, u32* texIds_CubeMap);
	int sendCurrentUsingProgram(u32 progId);
	int sendCurrentBindingVbos(u32 vboArrayBuffer, u32 vboElementArrayBuffer);

	bool receive(char* buffer, int len);
	bool receiveUint(u32& output);
	bool receiveInt(int& output);
	CaptureOption receiveCaptureOption();

	void close();

private:
	Socket m_socket;
};
