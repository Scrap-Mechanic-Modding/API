#include "PacketParser.hpp"
#include "Packets/C2S_ChatPacket.hpp"
#include "Packets/GenericPacket.hpp"
#include "Packets/Packet.hpp"

using namespace SMM::Network;

PacketParser::PacketParser()
{
}

PacketParser::~PacketParser()
{
}

/*
std::unordered_map<std::string, std::vector<packet_cb_t>> m_events;


for (auto& packet : m_packetQueue)
{
	Packet* pkt = Packet::Detect(packet->data(), packet->size());
	CB_Action action = parser->ForwardTo("OnPacket", processed);

	switch (action)
	{
		case ACTION_DROP:
			// drop packet
			break;
		case ACTION_MODIFY:
			// replace packet
			break;
		case default:
			// ignore
	};
}

*/

// Processes single packet
// Decompresses packets
// returns parsed packet
Packet* PacketParser::Process(void* t_data, size_t t_size)
{
    Packet* packet = nullptr;
    char* data = static_cast<char*>(t_data);

    switch (PacketID(data[0]))
    {
        case PacketID::C2S_ChatPacket:
            packet = new C2S_ChatPacket();
            break;
        default:
            packet = new GenericPacket();
            printf("[!] Unhandled packet ID: %u\n", data[0]);
            break;
    }

    if (!packet->Deserialize(data, t_size))
    {
    }

    return packet;
}

// Executes callbacks in sequence
PacketParser::CB_Action PacketParser::ForwardTo(std::string& t_eventName, Packet* t_packet)
{
    UNUSED(t_eventName);
    UNUSED(t_packet);

    return PacketParser::CB_Action::Pass;
}

int PacketParser::BindCallback(int t_packetID, packet_cb_t t_funcPtr, bool t_shouldBeValidation)
{
    UNUSED(t_packetID);
    UNUSED(t_funcPtr);
    UNUSED(t_shouldBeValidation);

    return 0;
}

bool PacketParser::UnbindCallback(int t_identifer)
{
    UNUSED(t_identifer);

    return false;
}
