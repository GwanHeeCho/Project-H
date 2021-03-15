#include "world.h"

void World::CWorld::connect(User::user_ptr user)
{
	m_user.insert(user);

	std::for_each(m_message.begin(), m_message.end(), boost::bind(&User::CUser::send, user, _1));
}

void World::CWorld::disconnect(User::user_ptr user)
{
	m_user.erase(user);
}

void World::CWorld::send(const Message::CData &msg)
{
	m_message.push_back(msg);
	while(messge < m_message.size())
	{
		m_message.pop_front();
	}
	
	std::for_each(m_user.begin(), m_user.end(), boost::bind(&User::CUser::send, _1, boost::ref(msg)));
}
