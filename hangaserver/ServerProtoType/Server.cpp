#include "Server.h"
#include <iostream>
#include "Session.h"

void Server::do_accept()
{
	_acceptor.async_accept([this](boost::system::error_code _ec, boost::asio::ip::tcp::socket _socket)
	{
		if (!_ec)
		{
			std::cout << "client join" << std::endl;
			std::make_shared<Session>(std::move(_socket))->start();
		}
		do_accept();
	});
}