#include "world.h"

void World::CWorld::connect(User::user_ptr user)
{
	m_user.insert(user);
	std::cout << user << " : client user connect" << std::endl;

	std::for_each(m_message.begin(), m_message.end(), boost::bind(&User::CUser::send, user, _1));
}

void World::CWorld::disconnect(User::user_ptr user)
{
	// �����ϸ� ���״µ� Ŭ�󿡼� ���� ��Ŷ�� ��û ũ�� ��Ŷ ���ް� �������
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
	
	// ��Ŷ Ȯ�ο�
	std::cout << msg.body() << std::endl;
	// ��ε�ĳ���� (Session Ŭ������ �̵�)
	std::for_each(m_user.begin(), m_user.end(), boost::bind(&User::CUser::send, _1, boost::ref(msg)));
}
