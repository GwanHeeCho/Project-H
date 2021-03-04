#pragma once
#include <flatbuffers/flatbuffers.h>


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