#include "Server.h"
#include <iostream>
#include "Session.h"


void Server::TCP::handleAccept()
{
	// https://jacking.tistory.com/1094 : ���ٸ� �̿��ؼ� �񵿱� �Լ� �����
	tcpAcceptor.async_accept([this](boost::system::error_code errorCode, boost::asio::ip::tcp::socket tcpSocket)
	{
		if (!errorCode)
		{
			std::cout << "client join" << std::endl;
			// https://pknam.tistory.com/14 : ��ü �����ϸ鼭 ����� �޸𸮿� control block�� ���� �޸𸮸� �ѹ��� �Ҵ� �޴´�.
			// https://modoocode.com/301 : ������ ���۷��� Ÿ������ lvalue�� ���� (������ �Ȼ��⵵��)
			// std::make_shared<Session>(std::move(tcpSocket))->start();
		}
		handleAccept();
	});
}