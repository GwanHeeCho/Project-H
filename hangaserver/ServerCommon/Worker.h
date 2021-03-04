#pragma once
// https://neive.tistory.com/303
// https://neive.tistory.com/22?category=403086
#include <boost/asio.hpp>
#include <boost/pool/pool.hpp>
#include <boost/function.hpp>
#include <boost/lockfree/queue.hpp>

typedef boost::function<void(BYTE*)> TYPE_SEND_CB;

struct WorkDate
{
	int id;
	int size;
	BYTE* pData;
};

class Worker
{
private:
	boost::pool<> m_Pool;
	boost::lockfree::queue<WorkDate> m_WorkList;
};

