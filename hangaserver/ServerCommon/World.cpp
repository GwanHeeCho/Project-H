#include "World.h"

void World::CWorld::connect(User::user_ptr user)
{
	// 서버에 정상적으로 입장한 유저를 set
	m_user.insert(user);
	// TODO: 0311 프토토타입 만들고 나중에 유저별로 구분하기 쉽도록 로깅 만들어서 ID 뿌리기
	std::cout << "User Join" << std::endl;

	// TODO: 0311 새로 입장한 유저에게 이전까지의 정보를 모두 넘겨주는 큐를 만들어서 제공하자
	std::for_each(m_message.begin(), m_message.end(), boost::bind(&User::CUser::send, user, _1));
}

void World::CWorld::disconnect(User::user_ptr user)
{
	// 나가길 원하는 유저 제외하기
	m_user.erase(user);
}

void World::CWorld::send(const Message::CData &msg)
{
	m_message.push_back(msg);
	while(messge < m_message.size())
	{
		m_message.pop_front();
	}
	// 유저들한테 메시지 다 뿌리기
	std::for_each(m_user.begin(), m_user.end(), boost::bind(&User::CUser::send, std::placeholders::_1, boost::ref(msg)));
}