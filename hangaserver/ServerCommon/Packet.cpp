#include "playerinfo_generated.h"
#include "Packet.h"

void Packet::SerializationPacket()
{
	flatbuffers::FlatBufferBuilder builder;
	
	auto name = builder.CreateString("ghcho");
	uint32_t level = 99;

	// 직렬화
	builder.Finish(CreatePlayerInfo(builder, name, level));

	// 직렬화된 버퍼 가져오기
	// 네트워크 보내거나 저장 가능. uint8_t 크기의 포인터값을 가지고 있음
	data = builder.GetBufferPointer();
	//uint32_t getLevel = builder.GetSize();
}

uint32_t Packet::DeserializationPacket()
{
	const PlayerInfo* playerinfo = GetPlayerInfo(data);
	
	return playerinfo->level();
}