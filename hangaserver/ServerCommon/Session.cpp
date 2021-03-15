#include "Session.h"

void Session::CSession::start()
{
	m_world.connect(shared_from_this());
	// async_read : ������ ������ ũ�Ⱑ ��� �� ������ ������ ����ؼ� ��ٸ��� �Լ�
	// buffer.size() = 4096 �ε� 7777 byte ũ���� ��Ŷ�� ���ŵ� ��쿡 4096 �����ϰ� ���� 3681Byte�� ���۵��� �ʴ´�.
	// ������ ���۸�ŭ ä���� �����ִ� �е� ����̳� ��Ƴ��� ���߿� �����ϴ� ����� ä���ؼ� ��������
	boost::asio::async_read(
		m_socket,
		boost::asio::buffer(m_read.data(), HEADER),
		boost::bind(&CSession::readHeader, shared_from_this(), boost::asio::placeholders::error)
	);
}

void Session::CSession::send(const Message::CData &message)
{
	bool writeProgress = !m_write.empty();
	m_write.push_back(message);

	if (!writeProgress)
	{
		boost::asio::async_write(
			m_socket,
			boost::asio::buffer(m_write.front().data(), m_write.front().length()),
			boost::bind(&CSession::write, shared_from_this(), boost::asio::placeholders::error)
		);
	}
}

void Session::CSession::readHeader(const boost::system::error_code &errorCode)
{
	if (!errorCode)
	{
		if (m_read.decode())
		{
			boost::asio::async_read(
				m_socket,
				boost::asio::buffer(m_read.body(), m_read.body_length()),
				boost::bind(&CSession::readBody, shared_from_this(), boost::asio::placeholders::error)
			);
		}
		else
		{
			m_world.disconnect(shared_from_this());
		}
	}
}

void Session::CSession::readBody(const boost::system::error_code &errorCode)
{
	if (!errorCode)
	{
		m_world.send(m_read);
		
		boost::asio::async_read(
			m_socket,
			boost::asio::buffer(m_read.data(), HEADER),
			boost::bind(&CSession::readHeader, shared_from_this(), boost::asio::placeholders::error)
			);
	}
	else
	{
		m_world.disconnect(shared_from_this());
	}
}

void Session::CSession::write(const boost::system::error_code &errorCode)
{
	if (!errorCode)
	{
		m_write.pop_front();

		if (!m_write.empty())
		{
			boost::asio::async_write(
				m_socket,
				boost::asio::buffer(m_write.front().data(), m_write.front().length()),
				boost::bind(&CSession::write, shared_from_this(), boost::asio::placeholders::error)
			);
		}
		else
		{
			m_world.disconnect(shared_from_this());
		}
	}
}


// ======================LEGACY=====================
//void Session::start()
//{
//	do_read();
//}
//
//void Session::do_read()
//{
//	// shared_from_this�� this �����͸� shared_ptr�� ���� �� �ִ� ������� ����Ű�� ���� �������� ���ϰ� ���´�.
//	// Server.cpp���� std::make_shared<Session>(std::move(tcpSocket))->start(); �ؼ� �����´�.
//	// self = std::shared_ptr<Session>
//	auto self(shared_from_this());
//
//	socket.async_read_some(boost::asio::buffer(_data, BUFFER_CHAR),
//		[this, self](boost::system::error_code errorCode, std::size_t length)
//	{
//		if (!errorCode)
//		{
//			do_write(length);
//		}
//	});
//}
//
//void Session::do_write(std::size_t length)
//{
//	auto self(shared_from_this());
//
//	boost::asio::async_write(socket, boost::asio::buffer(_data, length),
//		[this, self](boost::system::error_code errorCode, std::size_t /*length*/)
//		{
//			if (!errorCode)
//			{
//				do_read();
//			}
//		});
//}