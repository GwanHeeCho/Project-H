#include "world.h"

void World::CWorld::connect(User::user_ptr user)
{
	m_user.insert(user);
	std::cout << user << " : client user connect" << std::endl;

	std::for_each(m_message.begin(), m_message.end(), boost::bind(&User::CUser::send, user, _1));
}

void World::CWorld::disconnect(User::user_ptr user)
{
	// 웬만하면 안죽는데 클라에서 보낸 패킷이 엄청 크면 패킷 못받고 끊어버림
	std::cout << user << " : client user disconnect" << std::endl;
	m_user.erase(user);
}

void World::CWorld::send(const Message::CData &msg)
{
	m_message.push_back(msg);
	while(messge < m_message.size())
	{
		m_message.pop_front();
	}
	
	// 패킷 확인용
	std::cout << msg.body() << std::endl;
	// 브로드캐스팅 (Session 클래스로 이동)
	std::for_each(m_user.begin(), m_user.end(), boost::bind(&User::CUser::send, _1, boost::ref(msg)));
}
