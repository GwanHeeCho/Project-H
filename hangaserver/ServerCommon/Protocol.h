#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <iostream>
#include <iomanip>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include <deque>

#include "Enums.h"

namespace Message
{
	class CData
	{
	private:
		char packet[HEADER + BODY];
		size_t m_body_length;
	public:
		CData() : m_body_length(0)
		{
		}
	public:
		char* data();
		char* body();

		const char* data() const;
		const char* body() const;

		size_t length() const;
		size_t body_length() const;
		void body_length(size_t length);

		bool decode();
		void encode();
	};
	typedef std::deque<Message::CData> data_queue_ptr;
}

#endif