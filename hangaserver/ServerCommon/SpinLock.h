#pragma once
#include <Windows.h>
// https://github.com/bschiffthaler/BSlogger
// https://gist.github.com/jacking75/e9903613d7314083269aad63347112f2
const int SPIN_ROCK_COUNT = 1000;

class CSpinLock
{
private:
	CRITICAL_SECTION m_object;
public :
	CSpinLock();
	~CSpinLock();
	void Enter();
	void Leave();
};

class CSpinLockGuard
{
private:
	CSpinLock &m_spinlock;
public:
	CSpinLockGuard(CSpinLock &lock) : m_spinlock(lock)
	{
		m_spinlock.Enter();
	}
	~CSpinLockGuard()
	{
		m_spinlock.Leave();
	}
};