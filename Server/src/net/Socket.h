#pragma once

#if defined OS_WIN32
	#include <WinSock2.h>
	typedef SOCKET SocketHandle;
#else
	typedef int SocketHandle;
	#define INVALID_SOCKET (-1)
#endif

#define SOCKET_ERROR (-1)
#define SOCKET_SUCCESS (0)

class Socket
{
public:
	Socket();
	Socket(SocketHandle handle);
	int send(const char* buffer, int len);
	int receive(char* buffer, int len);
	void setReceiveTimeout(int ms);
	void close();
	bool receiveComplete(char* buffer, int len);
	
private:
	SocketHandle m_handle;
};
