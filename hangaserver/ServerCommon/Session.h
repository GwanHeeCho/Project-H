#pragma once
#include <memory>
#include "Enums.h"

#include "User.h"
#include "World.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <functional>

// https://chipmaker.tistory.com/entry/enablesharedfromthis-%EC%A0%95%EB%A6%AC
namespace Session
{
	class CSession : public User::CUser, public boost::enable_shared_from_this<CSession>
	{
	public:
		CSession(boost::asio::io_service &io_service, World::CWorld &io_world)
			: m_socket(io_service), m_world(io_world)
		{
		}
		boost::asio::ip::tcp::socket &socket()
		{
			return m_socket;
		}
	private:
		boost::asio::ip::tcp::socket m_socket;
		World::CWorld &m_world;
		Message::CData m_read;
		Message::message_ptr m_write; // dequeue ¿ëµµ
	public:
		void start();
		void send(const Message::CData &message);
		void readHeader(const boost::system::error_code &errorCode);
		void readBody(const boost::system::error_code &errorCode);
		void write(const boost::system::error_code &errorCode);
	};
	typedef boost::shared_ptr<CSession> session_ptr;
}