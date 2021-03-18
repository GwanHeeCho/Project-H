#pragma once
#include <boost/asio.hpp>
#include "Session.h"

namespace Server
{
	class TCPserver
	{
	private:
		boost::asio::io_service &service;
		boost::asio::ip::tcp::acceptor acceptor;
		World::CWorld world;
		
	public:
		TCPserver(boost::asio::io_service &io_service, const boost::asio::ip::tcp::endpoint &endpoint);
		void handleAccept(Session::session_ptr session, const boost::system::error_code &errorCode);
	};
	// TODO : make_shared ����ϱ�
	// std::make_shared<Session>(std::move(_socket))->start();
	// typedef std::make_shared<Server::TCPserver>(std::move(m_socket))->connect();
	typedef boost::shared_ptr<Server::TCPserver> server_ptr;
	typedef std::list<server_ptr> server_list;

	// https://gist.github.com/schtobia/9542961183ec7e0c8dd710baa39a7f8c
	// https://jacking.tistory.com/1094 : ���ٸ� �̿��ؼ� �񵿱� �Լ� �����
	// https://pknam.tistory.com/14 : ��ü �����ϸ鼭 ����� �޸𸮿� control block�� ���� �޸𸮸� �ѹ��� �Ҵ� �޴´�.
	// https://modoocode.com/301 : ������ ���۷��� Ÿ������ lvalue�� ���� (������ �Ȼ��⵵��)
}

