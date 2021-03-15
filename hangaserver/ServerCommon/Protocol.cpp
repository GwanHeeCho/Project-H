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
	strncat_s(header, packet, HEADER); // 패킷과 헤더를 합친다.
	m_body_length = boost::lexical_cast<size_t>(header); // atoi

	// 뭉쳐진 패킷이 큰 경우
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
	// 4칸 안쪽으로 바디길이 확인(데이터확인용)
	std::cout << std::setw(4) << m_body_length;
	// 이후 header만큼 메모리 복사해서 패킷 뒤에 붙여주기
	memcpy(packet, header, HEADER);
}