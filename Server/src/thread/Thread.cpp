#include "Thread.h"
#include "../log.h"

#if defined OS_WIN32
#include <Windows.h>

DWORD WINAPI Thread::MyThreadFunction(LPVOID lpParam)
{
	Data* data = (Data*)lpParam;
	(*data->func)(data->arg);
	return 0;
}

void Thread::start(Func func, void* arg)
{
	m_data.func = func;
	m_data.arg = arg;
	
	DWORD id;

	m_handle = CreateThread( 
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadFunction,       // thread function name
		&m_data,				// argument to thread function 
		0,                      // use default creation flags 
		&id);					// returns the thread identifier 
	if (m_handle == NULL)
	{
		LOGE("Could not CreateThread");
		return;
	}
}

void Thread::join()
{
	WaitForSingleObject(m_handle, INFINITE);
}

#else

#include <pthread.h>

void* Thread::MyThreadFunction(void* param)
{
	Data* data = (Data*)param;
	(*data->func)(data->arg);	
	return NULL;
}

void Thread::start(Func func, void* arg)
{
	m_data.func = func;
	m_data.arg = arg;
	int res = pthread_create(&m_handle, NULL, MyThreadFunction, &m_data);
	if (res)
	{
		LOGE("pthread_create error = %d", res);
	}
}

void Thread::join()
{
	pthread_join(m_handle, NULL);
}

#endif
