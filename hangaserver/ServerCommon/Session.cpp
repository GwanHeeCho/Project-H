#include "Session.h"

void Session::start()
{
	do_read();
}

void Session::do_read()
{
	auto self(shared_from_this());

	socket.async_read_some(boost::asio::buffer(_data, BUFFER_CHAR),
		[this, self](boost::system::error_code _ec, std::size_t _length)
	{
		if (!_ec)
		{
			do_write(_length);
		}
	});
}

void Session::do_write(std::size_t length)
{
	auto self(shared_from_this());

	boost::asio::async_write(socket, boost::asio::buffer(_data, length),
		[this, self](boost::system::error_code _ec, std::size_t /*length*/)
		{
			if (!_ec)
			{
				do_read();
			}
		});
}
