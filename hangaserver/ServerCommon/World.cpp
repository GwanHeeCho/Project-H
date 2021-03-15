#include "World.h"

void World::CWorld::connect(User::user_ptr user)
{
	// ������ ���������� ������ ������ set
	m_user.insert(user);
	// TODO: 0311 ������Ÿ�� ����� ���߿� �������� �����ϱ� ������ �α� ���� ID �Ѹ���
	std::cout << "User Join" << std::endl;

	// TODO: 0311 ���� ������ �������� ���������� ������ ��� �Ѱ��ִ� ť�� ���� ��������
	std::for_each(m_message.begin(), m_message.end(), boost::bind(&User::CUser::send, user, _1));
}

void World::CWorld::disconnect(User::user_ptr user)
{
	// ������ ���ϴ� ���� �����ϱ�
	m_user.erase(user);
}

void World::CWorld::send(const Message::CData &msg)
{
	m_message.push_back(msg);
	while(messge < m_message.size())
	{
		m_message.pop_front();
	}
	// ���������� �޽��� �� �Ѹ���
	std::for_each(m_user.begin(), m_user.end(), boost::bind(&User::CUser::send, std::placeholders::_1, boost::ref(msg)));
}