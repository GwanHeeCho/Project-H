#include "playerinfo_generated.h"
#include "Packet.h"

void Packet::SerializationPacket()
{
	flatbuffers::FlatBufferBuilder builder;
	
	auto name = builder.CreateString("ghcho");
	uint32_t level = 99;

	// ����ȭ
	builder.Finish(CreatePlayerInfo(builder, name, level));

	// ����ȭ�� ���� ��������
	// ��Ʈ��ũ �����ų� ���� ����. uint8_t ũ���� �����Ͱ��� ������ ����
	data = builder.GetBufferPointer();
	//uint32_t getLevel = builder.GetSize();
}

uint32_t Packet::DeserializationPacket()
{
	const PlayerInfo* playerinfo = GetPlayerInfo(data);
	
	return playerinfo->level();
}