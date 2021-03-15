#include <iostream>
#include <tchar.h>
#include <boost/asio.hpp>
#include <thread>
#include "Server.h"

int main()
{
	/*
	 * HangaServer.ini ���Ͽ��� HANGA_SERVER ��ü�� DefalutPort ��� �̸��� ���� Key�� ���� sizeof(io_port) ũ�⸸ŭ�� ���۸� �����ϰ� io_port�� Key�� Value�� ����
	 * ����, DefalutPort ��� Key�� ������ 3��° ������ PORT1�� ã�� �ش� Value�� �־�� (PORT1�� ������ �׳� �����ϰ� 0 ���� -> �̿����� ����ó�� �ʿ�)
	 * �ε�뷱���� ���� ������ �ƿ��� �ʿ��� ���, ini ���� �ϳ��� �������� ������ �����ϱ� �����ϴ�.
	 */
	TCHAR io_port[100];
	int getServerConfig = GetPrivateProfileString(_T("HANGA_SERVER"),_T("DefalutPort"),_T("PORT1"),
																_T(io_port), sizeof(io_port), _T(".\\HangaServer.ini"));

	if (getServerConfig == 0)
	{
		std::cout << "There is a problem with the contents of the Server Config file.";
		return -1;
	}
	
	try
	{
		boost::asio::io_context io_context;
		
		Server::TCP tcpServer(io_context, std::atoi(io_port));

		std::cout << "hanga server online" << std::endl;

		std::thread thread1([&io_context]() { io_context.run(); });
		std::thread thread2([&io_context]() { io_context.run(); });
		
		thread1.join();
		thread2.join();
		// UDP
		// Server::UDP udpServer("127.0.0.1", "11800");
		// udpServer.run();
	}
	catch (std::exception& errorCode)
	{
		std::cerr << "Exception: " << errorCode.what() << "\n";
	}

	return 0;
}