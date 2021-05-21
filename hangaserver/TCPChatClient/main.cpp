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
			// 4ĭ �������� �ٵ���� Ȯ��(������Ȯ�ο�)
			//std::cout << std::setw(4) << m_body_length;
			// ���� header��ŭ �޸� �����ؼ� ��Ŷ �ڿ� �ٿ��ֱ�
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
//		boost::asio::io_service io_service; // io_service�� �ϳ� �����Ѵ�. 
//
//		CProtocol protocol(io_service);
//	
//		boost::asio::detail::thread Join(boost::bind(&boost::asio::io_service::run, &io_service));
//		protocol.connect(); // ���� �õ� 
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
//		Join.join();   // �����尡 ����� ������ ���� �Լ��� ���Ḧ ���´� 
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