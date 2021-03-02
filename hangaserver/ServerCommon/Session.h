#pragma once
#include <memory>
#include <boost/asio.hpp>
#include "Enums.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
	boost::asio::ip::tcp::socket socket;
	char _data[BUFFER_CHAR];
public:
	Session(boost::asio::ip::tcp::socket _socket) : socket(std::move(_socket)) {}
	void start();
private:
	void do_read();
	void do_write(std::size_t length);
};
