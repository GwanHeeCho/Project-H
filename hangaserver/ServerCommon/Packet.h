#pragma once
#include "Protocol.h"

class Packet
{
private:
	const uint8_t* data = nullptr;
	Packet();
	~Packet();
public:
	void SerializationPacket();
	uint32_t DeserializationPacket();
};