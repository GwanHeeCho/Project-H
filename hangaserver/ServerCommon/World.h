#pragma once

#include <set>
#include "User.h"
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace World
{
	class CWorld
	{
	private:
		std::set<User::user_ptr> m_user;
		Message::message_ptr m_message;
		enum { messge = 0 };
	public:
		void connect(User::user_ptr user);
		void disconnect(User::user_ptr user);
		void send(const Message::CData &msg);
	};
}