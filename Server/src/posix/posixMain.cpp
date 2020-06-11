#include "../app.h"
#include "../Server.h"

extern Server server;

void KPSwapBuffers()
{
	server.onSwapBuffers();
}

extern "C" void C_KPSwapBuffers()
{
	KPSwapBuffers();
}

class Dummy
{
public:
	Dummy()
	{
		startServerThread();
	}
	~Dummy()
	{
		stopServerThread();
	}
} dummy;
