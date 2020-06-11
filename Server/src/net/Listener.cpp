#include "Listener.h"
#include "Socket.h"
#include <stdio.h>
#include <string.h>
#include "../log.h"

#if defined OS_WIN32

#include <WinSock2.h>
#include <ws2tcpip.h>

Listener::Listener() : m_listenSocketHandle(INVALID_SOCKET)
{
}

Listener::~Listener()
{
	close();
}

void Listener::start(int port)
{
	WSADATA wsaData;
	int r = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (r != 0) {
		LOGE("WSAStartup failed: %d", r);
		return ;
	}

	char buffer[10];
	sprintf(buffer, "%d", port);
	struct addrinfo *result = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	r = getaddrinfo(NULL, buffer, &hints, &result);

	if (r != 0)
	{
		LOGE("getaddrinfo failed: %d", r);
		WSACleanup();
		return;
	}

	m_listenSocketHandle = INVALID_SOCKET;
	m_listenSocketHandle = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (m_listenSocketHandle == INVALID_SOCKET)
	{
		LOGE("Error at socket(): %ld", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	r = bind(m_listenSocketHandle, result->ai_addr, (int)result->ai_addrlen);
	if (r == SOCKET_ERROR)
	{
		LOGE("bind failed with error: %d", WSAGetLastError());
		freeaddrinfo(result);
		close();
		WSACleanup();
		return;
	}
	
	freeaddrinfo(result);

	r = listen(m_listenSocketHandle, SOMAXCONN);
	if (r == SOCKET_ERROR)
	{
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		close();
		WSACleanup();
		return;
	}

	LOGD("Listener::start OK!!!");
}

Socket Listener::accept()
{
	return Socket(::accept(m_listenSocketHandle, NULL, NULL));
}

bool Listener::isListening()
{
	return m_listenSocketHandle != INVALID_SOCKET;
}

void Listener::close()
{
	closesocket(m_listenSocketHandle);
	m_listenSocketHandle = INVALID_SOCKET;
}

#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Listener::Listener() : m_listenSocketHandle(INVALID_SOCKET)
{
}

Listener::~Listener()
{
	close();
}

void Listener::start(int port)
{
	sockaddr_in serverAddr;
	m_listenSocketHandle = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	bind(m_listenSocketHandle, (sockaddr*)&serverAddr, sizeof(serverAddr));

	listen(m_listenSocketHandle, SOMAXCONN);
	LOGD("Listener::start OK!!!");
}

Socket Listener::accept()
{
	return Socket(::accept(m_listenSocketHandle, NULL, NULL));
}

bool Listener::isListening()
{
	return m_listenSocketHandle != INVALID_SOCKET;
}

void Listener::close()
{
	::close(m_listenSocketHandle);
	m_listenSocketHandle = INVALID_SOCKET;
}

#endif
