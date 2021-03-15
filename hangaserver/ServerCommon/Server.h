#pragma once
#include <boost/asio.hpp>
#include "Session.h"

namespace Server
{
	class TCP
	{
	private:
		boost::asio::ip::tcp::acceptor tcpAcceptor;
	private:
		void handleAccept();
	public:
		TCP(boost::asio::io_context& io_context, short port)
			: tcpAcceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
		{
			handleAccept();
		}
	};

	class TCPserver
	{
	private:
		boost::asio::io_context& ioContext;
		boost::asio::ip::tcp::acceptor tcpAcceptor;
		World::CWorld m_world;
		
	public:
		TCPserver(boost::asio::io_service, const boost::asio::ip::tcp::endpoint &endpoint);
		void handleAccept();
	};
	typedef boost::shared_ptr<Server::TCPserver> server_ptr;
	typedef std::list<server_ptr> server_list;

	// https://gist.github.com/schtobia/9542961183ec7e0c8dd710baa39a7f8c
	class UDP
	{
	private:
		boost::asio::io_context io_context;
	public:
		UDP(std::string address, std::string port);
		void run();
	};
}

