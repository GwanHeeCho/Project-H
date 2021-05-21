//#pragma once
//#include <boost/asio/io_service.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <iostream>
//
//const std::string IP("127.0.0.1");
//const std::string PORT("10800");
//
//class CProtocol
//{
//private:
//	enum { buffer = 128, };
//	
//	boost::asio::ip::tcp::socket m_socket;
//	bool m_connect;
//	int m_count;
//public:
//	CProtocol(boost::asio::io_service &io_service) : m_socket(io_service)
//	{
//		m_connect = false;
//		m_count = 0;
//	}
//	~CProtocol()
//	{
//	}
//public:
//	void connect();
//	bool run();
//	bool socketOpen();
//	void handleRecive();
//	void handleSend();
//};
