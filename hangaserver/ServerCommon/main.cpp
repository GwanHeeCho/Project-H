#include <iostream>
#include <tchar.h>
#include <boost/asio.hpp>
#include <thread>
#include "Server.h"

int main()
{
	/*
	 * HangaServer.ini 파일에서 HANGA_SERVER 객체의 DefalutPort 라는 이름을 가진 Key의 값을 sizeof(io_port) 크기만큼의 버퍼를 생성하고 io_port에 Key의 Value를 삽입
	 * 만약, DefalutPort 라는 Key가 없으면 3번째 인자의 PORT1를 찾아 해당 Value를 넣어라 (PORT1가 없으면 그냥 무시하고 0 대입 -> 이에대한 예외처리 필요)
	 * 로드밸런싱을 위한 스케일 아웃이 필요한 경우, ini 파일 하나로 여러대의 서버를 관리하기 용이하다.
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