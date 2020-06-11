#pragma once

#include "Socket.h"

class Listener
{
public:
	Listener();
	~Listener();

	void start(int port);
	Socket accept();
	void close();
	bool isListening();

private:
	SocketHandle m_listenSocketHandle;
};
