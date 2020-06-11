#include "Socket.h"
#include "../log.h"

Socket::Socket() : Socket(INVALID_SOCKET)
{
}

Socket::Socket(SocketHandle handle) : m_handle(handle)
{
}

#if defined OS_WIN32
#include <WinSock2.h>

int Socket::send(const char* buffer, int len)
{
	return ::send(m_handle, buffer, len, 0);
}

int Socket::receive(char* buffer, int len)
{
	return ::recv(m_handle, buffer, len, 0);
}

void Socket::setReceiveTimeout(int ms)
{
	DWORD val = (DWORD)ms;
	setsockopt(m_handle,
		SOL_SOCKET,
		SO_RCVTIMEO,
		(const char *)&val,
		sizeof(val));
}

void Socket::close()
{
	::closesocket(m_handle);
}

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int Socket::send(const char* buffer, int len)
{
	return ::send(m_handle, buffer, len, 0);
}

int Socket::receive(char* buffer, int len)
{
	return ::recv(m_handle, buffer, len, 0);
}

void Socket::setReceiveTimeout(int ms)
{
	struct timeval timeout;
	timeout.tv_sec = ms / 1000;
	timeout.tv_usec = (ms % 1000) * 1000;

	if (setsockopt(m_handle, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	{
		LOGE("setsockopt failed SO_RCVTIMEO, ms = %d", ms);
		return;
	}
}

void Socket::close()
{
	::close(m_handle);
}

#endif

bool Socket::receiveComplete(char* buffer, int len)
{
	const int MAX_RETRY_COUNT = 3;
	char* buf = buffer;
	int bytesRead = 0;
	int retryCount = 0;
	while (bytesRead < len)
	{
		int r = this->receive(buf, len - bytesRead);
		if (r < 0) return false;
		if (r == 0)
		{
			retryCount++;
			if (retryCount > MAX_RETRY_COUNT)
			{
				LOGE("Timeout in [%s]", __FUNCTION__);
				return false;
			}
		}
		else
		{
			retryCount = 0;
		}
		buf += r;
		bytesRead += r;
	}

	return true;
}
