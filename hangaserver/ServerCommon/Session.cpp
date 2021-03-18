#include "Session.h"

void Session::CSession::start()
{
	m_world.connect(shared_from_this());
	
	// shared_from_this�� this �����͸� shared_ptr�� ���� �� �ִ� ������� ����Ű�� ���� �������� ���ϰ� ���´�.
	auto self(shared_from_this());
	
	m_socket.async_read_some(
		boost::asio::buffer(m_read.data(), HEADER),
		[this, self](boost::system::error_code errorCode, size_t /*length*/)
		{
			if (!errorCode)
			{
				readHeader(errorCode);
			}
		}
	);
}

void Session::CSession::send(const Message::CData &message)
{
	bool writeProgress = !m_write.empty();
	m_write.push_back(message);

	if (!writeProgress)
	{
		auto self(shared_from_this());
		boost::asio::async_write(
			m_socket,
			boost::asio::buffer(m_write.front().data(), m_write.front().length()),
			[this, self](boost::system::error_code errorCode, size_t /*length*/)
			{
				write(errorCode);
			}
		);
	}
}

void Session::CSession::readHeader(const boost::system::error_code &errorCode)
{
	if (!errorCode)
	{
		if (m_read.decode())
		{
			auto self(shared_from_this());
			
			m_socket.async_read_some(
				boost::asio::buffer(m_read.body(), m_read.body_length()),
				[this, self](boost::system::error_code errorCode, size_t /*length*/)
				{
					if (!errorCode)
					{
						readBody(errorCode);
					}
				}
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
	auto self(shared_from_this());
	
	if (!errorCode)
	{
		m_write.pop_front();

		if (!m_write.empty())
		{
			
			boost::asio::async_write(
				m_socket,
				boost::asio::buffer(m_write.front().data(), m_write.front().length()),
				[this, self](boost::system::error_code errorCode, std::size_t /*length*/)
				{
					if (errorCode)
					{
						m_world.disconnect(shared_from_this());
					}
				}
			);
		}
	}
	else
	{
		m_world.disconnect(self);
	}
}

// async_read : ������ ������ ũ�Ⱑ ��� �� ������ ������ ����ؼ� ��ٸ��� �Լ�
// buffer.size() = 4096 �ε� 7777 byte ũ���� ��Ŷ�� ���ŵ� ��쿡 4096 �����ϰ� ���� 3681Byte�� ���۵��� �ʴ´�.
// ������ ���۸�ŭ ä���� �����ִ� �е� ����̳� ��Ƴ��� ���߿� �����ϴ� ����� ä���ؼ� ��������
/*
boost::asio::async_read(
	m_socket,
	boost::asio::buffer(m_read.data(), HEADER),
	boost::bind(&CSession::readHeader, shared_from_this(), boost::asio::placeholders::error)
);
boost::asio::async_write(
		m_socket,
		boost::asio::buffer(m_write.front().data(), m_write.front().length()),
		boost::bind(&CSession::write, shared_from_this(), boost::asio::placeholders::error)
	);
*/