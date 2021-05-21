//#include "Protocol.h"
//
//#include <boost/lexical_cast.hpp>
//#include <boost/asio/write.hpp>
//
//void CProtocol::connect()
//{
//	// �Է� ���� host�� resolving�Ѵ�. 
//	tcp::resolver resolver(m_socket.get_io_service());
//	tcp::resolver::query query(IP, "daytime");
//	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
//	tcp::resolver::iterator end;
//
//	// resolving�� endpoint�� ������ �õ��Ѵ�. 
//	boost::system::error_code error = boost::asio::error::host_not_found;
//	while (error && endpoint_iterator != end)
//	{
//		m_socket.close();
//		m_socket.connect(*endpoint_iterator++, error);
//	}
//
//	// ���� �������� Ȯ�� 
//	if (error)
//		throw boost::system::system_error(error);
//
//	m_connect = true;
//
//	// �о�� �����͸� ������ array�� �����. 
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
//	// ���� �����͸� cout�� ����Ѵ�. 
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
//	if (!m_socket.is_open() && m_connect)   // Ŀ��Ʈ �� ���� ������ �������ȴٸ� 
//	{
//		m_connect = false;                 // Ŀ��Ʈ�� ���� ���� 
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