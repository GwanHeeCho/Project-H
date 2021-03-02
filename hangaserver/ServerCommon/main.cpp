#include <iostream>
#include <boost/asio.hpp>
#include "Server.h"

int main()
{
	try
	{
		boost::asio::io_context io_context;

		Server s(io_context, 10800);
		std::cout << "asncy hanga server online" << std::endl;
		io_context.run();
	}
	catch (std::exception& _ec)
	{
		std::cerr << "Exception: " << _ec.what() << "\n";
	}

	return 0;
}
