#pragma once

class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();

private:
	void* m_handle;
};

struct LockScope
{
	LockScope(Mutex& mutex) : m_mutex(mutex)
	{
		m_mutex.lock();
	}
	~LockScope()
	{
		m_mutex.unlock();
	}
	Mutex& m_mutex;
};
