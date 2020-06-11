#include "Mutex.h"
#include <stdlib.h>

#ifdef OS_WIN32
#include <windows.h>

Mutex::Mutex()
{
	m_handle = CreateMutex(NULL, FALSE, NULL);
}

Mutex::~Mutex()
{
	CloseHandle(m_handle);
}

void Mutex::lock()
{
	WaitForSingleObject(m_handle, INFINITE);
}

void Mutex::unlock()
{
	ReleaseMutex(m_handle);
}

#else

#include <pthread.h>

Mutex::Mutex() 
{        
	m_handle = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((pthread_mutex_t*)m_handle, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy((pthread_mutex_t*)m_handle);
	free(m_handle);
}

void Mutex::lock()
{
	pthread_mutex_lock((pthread_mutex_t*)m_handle);
}

void Mutex::unlock()
{
	pthread_mutex_unlock((pthread_mutex_t*)m_handle);
}

#endif
