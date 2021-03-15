#pragma once
#include <boost/scope_exit.hpp>

template <typename T>
class CSingleton
{
private:
	static T* m_instance;
public:
	CSingleton();
	virtual ~CSingleton();
	static T* getSingleton();
	inline static void delSingleton();
};

template <typename T>
__declspec(selectany) T* CSingleton<T>::m_instance = nullptr;