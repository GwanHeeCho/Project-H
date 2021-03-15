#pragma once
#include <memory>
#include "Enums.h"

#include "User.h"
#include "World.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <functional>

//class Session : public std::enable_shared_from_this<Session>
//{
//public:
//	boost::asio::ip::tcp::socket socket;
//	char _data[BUFFER_CHAR];
//public:
//	Session(boost::asio::ip::tcp::socket tcpSsocket) : socket(std::move(tcpSsocket)) {}
//	void start();
//private:
//	void do_read();
//	void do_write(std::size_t length);
//};

// https://chipmaker.tistory.com/entry/enablesharedfromthis-%EC%A0%95%EB%A6%AC
namespace Session
{
	class CSession : public User::CUser, public boost::enable_shared_from_this<CSession>
	{
	private:
		boost::asio::ip::tcp m_socket;
		World::world_ptr& m_world;
		Message::CData m_read;
		Message::data_queue_ptr m_write; // dequeue ¿ëµµ	
	public:
		void start();
		void send(const Message::CData &message);
		void readHeader(const boost::system::error_code &errorCode);
		void readBody(const boost::system::error_code &errorCode);
		void write(const boost::system::error_code &errorCode);
	};
	typedef boost::shared_ptr<CSession> session_ptr;
}