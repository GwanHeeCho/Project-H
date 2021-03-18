#include "Server.h"
#include <iostream>
#include "Session.h"

Server::TCPserver::TCPserver(boost::asio::io_service &io_service, const boost::asio::ip::tcp::endpoint &endpoint)
	: service(io_service), acceptor(io_service, endpoint)
{
	Session::session_ptr new_session(new Session::CSession(service, world));
	acceptor.async_accept(new_session->socket(),
		boost::bind(&TCPserver::handleAccept, this, new_session, boost::asio::placeholders::error));
}

void Server::TCPserver::handleAccept(Session::session_ptr session, const boost::system::error_code &errorCode)
{
	if (!errorCode)
	{
		session->start();
		Session::session_ptr new_session(new Session::CSession(service, world));

		acceptor.async_accept(new_session->socket(),
			boost::bind(&TCPserver::handleAccept, this, new_session, boost::asio::placeholders::error));

		std::string remote_ip = session->socket().remote_endpoint().address().to_string();
		unsigned short remote_port = session->socket().remote_endpoint().port();

		std::cout << "Join to Client connected : " << remote_ip.c_str() << "(" << remote_port << ")" << std::endl;
	}
}
