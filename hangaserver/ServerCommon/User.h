#pragma once
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Protocol.h"

namespace User
{
	class CUser
	{
	public:
		virtual ~CUser();
		virtual void send(const Message::CData& msg) = 0;
	};
	typedef boost::shared_ptr<CUser> user_ptr;
}