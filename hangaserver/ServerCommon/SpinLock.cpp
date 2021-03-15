#include "SpinLock.h"

CSpinLock::CSpinLock()
{
	// 실패하면 로그띄워서 뭐때문인지 원인파악
	InitializeCriticalSectionAndSpinCount(&m_object, SPIN_ROCK_COUNT);
}

CSpinLock::~CSpinLock()
{

}

void CSpinLock::Enter()
{
	::EnterCriticalSection(&m_object);
}

void CSpinLock::Leave()
{
	::LeaveCriticalSection(&m_object);
}