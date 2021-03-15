#include "Singleton.h"

template <typename T>
CSingleton<T>::CSingleton()
{

}

template <typename T>
CSingleton<T>::~CSingleton()
{

}

template <typename T>
T* CSingleton<T>::getSingleton()
{
	if (m_instance == nullptr)
		m_instance = new T;
	
	return m_instance;
}

template <typename T>
void CSingleton<T>::delSingleton()
{
	SAFE_DELETE(m_instance);
}