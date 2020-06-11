#pragma once

#ifdef OS_WIN32
	#include <Windows.h>
	typedef HANDLE ThreadHandle;
#else
	#include <pthread.h>
	typedef pthread_t ThreadHandle;
#endif

class Thread
{
public:
	typedef void (*Func)(void* arg);
	
	void start(Func func, void* arg);
	void join();

private:
	struct Data
	{
		Func func;
		void* arg;
	};

	Data m_data;
	ThreadHandle m_handle;

#ifdef OS_WIN32
	static DWORD WINAPI MyThreadFunction(LPVOID lpParam);
#else
	static void* MyThreadFunction(void* param);
#endif
};
