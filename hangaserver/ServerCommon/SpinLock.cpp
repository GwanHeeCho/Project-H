#include "SpinLock.h"

CSpinLock::CSpinLock()
{
	// �����ϸ� �α׶���� ���������� �����ľ�
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