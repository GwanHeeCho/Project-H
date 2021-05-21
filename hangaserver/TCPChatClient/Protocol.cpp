//#include "Protocol.h"
//
//#include <boost/lexical_cast.hpp>
//#include <boost/asio/write.hpp>
//
//void CProtocol::connect()
//{
//	// 입력 받은 host을 resolving한다. 
//	tcp::resolver resolver(m_socket.get_io_service());
//	tcp::resolver::query query(IP, "daytime");
//	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//	tcp::resolver::iterator end;
//
//	// resolving된 endpoint로 접속을 시도한다. 
//	boost::system::error_code error = boost::asio::error::host_not_found;
//	while (error && endpoint_iterator != end)
//	{
//		m_socket.close();
//		m_socket.connect(*endpoint_iterator++, error);
//	}
//
//	// 접속 실패인지 확인 
//	if (error)
//		throw boost::system::system_error(error);
//
//	m_connect = true;
//
//	// 읽어올 데이터를 저장할 array를 만든다. 
//	boost::array<CHAR, buffer> buf;
//	size_t len = m_socket.read_some(boost::asio::buffer(buf), error);
//	if (error == boost::asio::error::eof)
//	{
//		m_connect = false;
//		return;
//	}
//	else if (error)
//		throw boost::system::system_error(error);
//
//	// 받은 데이터를 cout로 출력한다. 
//	std::cout.write(buf.data(), len);
//}
//
//bool CProtocol::run()
//{
//	return m_connect;
//}
//
//bool CProtocol::socketOpen()
//{
//	if (!m_socket.is_open() && m_connect)   // 커넥트 된 이후 소켓이 닫혀버렸다면 
//	{
//		m_connect = false;                 // 커넥트도 끊김 판정 
//		return false;
//	}
//
//	return true;
//}
//
//void CProtocol::handleRecive()
//{
//	while (m_connect)
//	{
//		if (!socketOpen())
//			break;
//
//		try
//		{
//			boost::array<BYTE, buffer> buf;
//			int len = m_socket.receive(boost::asio::buffer(buf));
//			if (len > 0)
//			{
//				std::cout << "> Recv(len " << len << ") ";
//				std::cout.write((CHAR*)buf.data(), len) << std::endl;
//			}
//		}
//		catch (std::exception& e)
//		{
//			m_connect = false;
//			std::cerr << e.what() << std::endl;
//		}
//	}
//}
//
//void CProtocol::handleSend()
//{
//	while (m_connect)
//	{
//		if (!socketOpen())
//			break;
//
//		try
//		{
//			boost::array<BYTE, buffer> buf = { boost::lexical_cast<BYTE>(m_count) };
//			boost::system::error_code error;
//			int len = boost::asio::write(m_socket, boost::asio::buffer(buf, buf.size()), error);
//			if (len > 0)
//				std::cout << "> Send " << m_count << std::endl;
//			m_count++;
//		}
//		catch (std::exception& e)
//		{
//			m_connect = false;
//			std::cerr << e.what() << std::endl;
//		}
//
//		Sleep(3000);
//	}
//}