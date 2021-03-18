#include <iostream>
#include <tchar.h>
#include <boost/asio.hpp>
#include <thread>
#include "Server.h"

int _tmain(int argc, _TCHAR* argv[]){
	/*
	 * HangaServer.ini ���Ͽ��� HANGA_SERVER ��ü�� PORT ��� �̸��� ���� Key�� ���� sizeof(io_port) ũ�⸸ŭ�� ���۸� �����ϰ� io_port�� Key�� Value�� ����
	 * ����, PORT ��� Key�� ������ 3��° ������ PORT1�� ã�� �ش� Value�� �־�� (PORT1�� ������ �׳� �����ϰ� 0 ���� -> �̿����� ����ó�� �ʿ�)
	 * �ε�뷱���� ���� ������ �ƿ��� �ʿ��� ���, ini ���� �ϳ��� �������� ������ �����ϱ� �����ϴ�.
	 */
	TCHAR io_port[100];
	int getServerConfig = GetPrivateProfileString(_T("HANGA_SERVER"), _T("PORT"), _T("PORT1"),
		_T(io_port), sizeof(io_port), _T(".\\..\\ServerCommon\\HangaServer.ini"));

	if (getServerConfig == 0)
	{
		std::cout << "There is a problem with the contents of the Server Config file.";
		return -1;
	}

	try
	{
		boost::asio::io_service io_service;
		Server::server_list server_list;
		
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), atoi(io_port));
		
		Server::server_ptr server(new Server::TCPserver(io_service, endpoint));
		// std::shared_ptr<Server::TCPserver> server_ptr = std::make_shared<Server::TCPserver>(io_service, endpoint);
		
		server_list.push_back(server);

		std::cout << "hanga Server Online (" << io_port << ")" << std::endl;
		
		io_service.run();
		
		/*std::thread thread1([&io_service]() { io_service.run(); });
		std::thread thread2([&io_service]() { io_service.run(); });
		thread1.join();
		thread2.join();*/
	}
	catch (std::exception& errorCode)
	{
		std::cerr << "Exception:` " << errorCode.what() << "\n";
	}

	return 0;
}