#include "Protocol.h"

char * Message::CData::data()
{
	return packet;
}
const char* Message::CData::data() const
{
	return packet;
}

char* Message::CData::body()
{
	return packet + HEADER;
}
const char* Message::CData::body() const
{
	return packet + HEADER;
}

size_t Message::CData::length() const
{
	return HEADER + m_body_length;
}
size_t Message::CData::body_length() const
{
	return m_body_length;
}
void Message::CData::body_length(size_t length)
{
	m_body_length = length;
	if (m_body_length > BODY)
		m_body_length = BODY;
}

bool Message::CData::decode()
{
	char header[HEADER + 1] = "";
	strncat_s(header, packet, HEADER); // ��Ŷ�� ����� ��ģ��.
	m_body_length = boost::lexical_cast<size_t>(header); // atoi

	// ������ ��Ŷ�� ū ���
	if (m_body_length > BODY)
	{
		m_body_length = 0;
		return false;
	}
	return true;
}

void Message::CData::encode()
{
	char header[HEADER + 1] = "";
	// 4ĭ �������� �ٵ���� Ȯ��(������Ȯ�ο�)
	std::cout << std::setw(4) << m_body_length;
	// ���� header��ŭ �޸� �����ؼ� ��Ŷ �ڿ� �ٿ��ֱ�
	memcpy(packet, header, HEADER);
}