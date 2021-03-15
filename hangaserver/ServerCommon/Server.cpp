#include "Server.h"
#include <iostream>
#include "Session.h"


void Server::TCP::handleAccept()
{
	// https://jacking.tistory.com/1094 : 람다를 이용해서 비동기 함수 만들기
	tcpAcceptor.async_accept([this](boost::system::error_code errorCode, boost::asio::ip::tcp::socket tcpSocket)
	{
		if (!errorCode)
		{
			std::cout << "client join" << std::endl;
			// https://pknam.tistory.com/14 : 객체 생성하면서 생기는 메모리와 control block을 위한 메모리를 한번에 할당 받는다.
			// https://modoocode.com/301 : 우측값 레퍼런스 타입으로 lvalue를 대입 (생성자 안생기도록)
			// std::make_shared<Session>(std::move(tcpSocket))->start();
		}
		handleAccept();
	});
}