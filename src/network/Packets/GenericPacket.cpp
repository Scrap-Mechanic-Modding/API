#include "../../common.hpp"
#include "GenericPacket.hpp"
#include "Packet.hpp"

using namespace SMM;

size_t Network::GenericPacket::Serialize(char* t_dst, size_t t_maxDstSize)
{
    UNUSED(t_dst);
    UNUSED(t_maxDstSize);
    return 0;
}

bool Network::GenericPacket::Deserialize(char* t_packetData, size_t t_packetSize)
{
    UNUSED(t_packetData);
    UNUSED(t_packetSize);
    return false;
}

size_t Network::GenericPacket::GetSize()
{
    return 0;
}