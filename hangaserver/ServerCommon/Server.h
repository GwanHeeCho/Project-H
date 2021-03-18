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
	// TODO : make_shared 사용하기
	// std::make_shared<Session>(std::move(_socket))->start();
	// typedef std::make_shared<Server::TCPserver>(std::move(m_socket))->connect();
	typedef boost::shared_ptr<Server::TCPserver> server_ptr;
	typedef std::list<server_ptr> server_list;

	// https://gist.github.com/schtobia/9542961183ec7e0c8dd710baa39a7f8c
	// https://jacking.tistory.com/1094 : 람다를 이용해서 비동기 함수 만들기
	// https://pknam.tistory.com/14 : 객체 생성하면서 생기는 메모리와 control block을 위한 메모리를 한번에 할당 받는다.
	// https://modoocode.com/301 : 우측값 레퍼런스 타입으로 lvalue를 대입 (생성자 안생기도록)
}

