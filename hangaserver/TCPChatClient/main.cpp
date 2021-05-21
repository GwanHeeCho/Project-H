#include <iostream>
#include <boost/asio.hpp>
#include <iomanip>

#define HEADER 4
#define BODY 2048

int main ()
{
	char packet[HEADER + BODY];
	size_t m_body_length;
	
	try
	{
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket io_socket(io_service);
		boost::asio::ip::tcp::resolver io_resolver(io_service);
		boost::asio::connect(io_socket, io_resolver.resolve("127.0.0.1", "10800"));

		while (1)
		{
			char header[HEADER + 1] = "";
			// 4칸 안쪽으로 바디길이 확인(데이터확인용)
			//std::cout << std::setw(4) << m_body_length;
			// 이후 header만큼 메모리 복사해서 패킷 뒤에 붙여주기
			memcpy(packet, header, HEADER);

			//m_pClientSocket->Send(strDataPack, strDataPack.GetLength());
		}
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}
	return 0;
}

//#include <iostream>
//
//
//#include "Protocol.h"
//#include "../../library/boost_1_70_0/boost/asio/io_service.hpp"
//#include "../../library/boost_1_70_0/boost/asio/ip/tcp.hpp"
//#include "../../library/boost_1_70_0/boost/bind/bind.hpp"
//
//using namespace std;
//
//int _tmain(int argc, char* argv[])
//{
//	try
//	{
//		boost::asio::io_service io_service; // io_service를 하나 생성한다. 
//
//		CProtocol protocol(io_service);
//	
//		boost::asio::detail::thread Join(boost::bind(&boost::asio::io_service::run, &io_service));
//		protocol.connect(); // 접속 시도 
//		boost::asio::detail::thread Recv(boost::bind(&CProtocol::handleRecive, &protocol));
//		boost::asio::detail::thread Send(boost::bind(&CProtocol::handleSend, &protocol));
//		io_service.run();
//
//		while (protocol.run())
//		{
//		}
//
//		Recv.join();
//		Send.join();
//
//		Join.join();   // 쓰레드가 종료될 때까지 메인 함수의 종료를 막는다 
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << e.what() << std::endl;
//	}
//
//	int in;
//	std::cout << "END";
//	std::cin >> in;
//
//	return 0;
//}