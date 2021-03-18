#pragma once
#include <boost/asio.hpp>

class Server
{
private:
	boost::asio::ip::tcp::acceptor _acceptor;
private:
	void do_accept();
public:
	Server(boost::asio::io_context& io_context, short port)
		: _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
	{
		do_accept();
	}
};