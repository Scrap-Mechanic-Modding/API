#include "../../utility/ByteStream.hpp"
#include "../CompressionHelper.hpp"
#include "C2S_ChatPacket.hpp"
#include "Packet.hpp"

using namespace SMM::Network;

size_t C2S_ChatPacket::GetSize()
{
    size_t size = 1;

    size += sizeof(m_databaseID);
    size += sizeof(m_channelID);
    size += sizeof(m_worldID);
    size += sizeof(m_flags);
    size += sizeof(m_mystery);
    size += 3;
    size += sizeof(m_timestamp);
    size += sizeof(m_playerNameSize);
    size += m_playerNameSize;
    size += sizeof(m_messageSize);
    size += m_messageSize;

    return size;
}

size_t C2S_ChatPacket::Serialize(char* t_dst, size_t t_maxDstSize)
{
    if (GetSize() > t_maxDstSize)
    {
        return 0;
    }
    CompressionHelper* c_helper = CompressionHelper::GetInstancePtr();
    ByteStream stream(c_helper->GetGlobalBuffer(), c_helper->GetGlobalBufferSize());

    try
    {
        stream.Write<PacketID>(m_id);
        stream.Write<unsigned int>(m_databaseID);
        stream.Write<unsigned short>(m_channelID);
        stream.Write<unsigned char>(m_worldID);
        stream.Write<unsigned int>(m_flags);
        stream.Write<unsigned int>(m_mystery);
        stream.WriteByte(0x0, 3);
        stream.Write<time_t>(m_timestamp);
        stream.Write<unsigned short>(m_playerNameSize);
        stream.WriteBytesStr(m_playerName);
        stream.Write<unsigned short>(m_messageSize);
        stream.WriteBytesStr(m_message);

    } catch (std::runtime_error error)
    {

        return 0;
    }

    c_helper->SetBuffer(t_dst, t_maxDstSize);
    return c_helper->Compress(c_helper->GetGlobalBuffer(), GetSize());
}

bool C2S_ChatPacket::Deserialize(char* t_packetData, size_t t_packetSize)
{
    CompressionHelper* c_helper = CompressionHelper::GetInstancePtr();
    size_t real_size = c_helper->Decompress(t_packetData, t_packetSize);
    if (real_size < 0)
    {
        return false;
    }

    //TODO: a const / read-only readstream would be better for these situations
    ByteStream stream(c_helper->GetGlobalBuffer(), real_size);

    try
    {
        stream.Skip(1);
        m_databaseID = stream.Read<unsigned int>();
        m_channelID = stream.Read<unsigned short>();
        m_worldID = stream.Read<unsigned char>();
        m_flags = stream.Read<unsigned int>();
        m_mystery = stream.Read<unsigned int>();
        stream.Skip(3);
        m_timestamp = stream.Read<time_t>();
        m_playerNameSize = stream.Read<unsigned short>();
        m_playerName = stream.ReadBytesStr(m_playerNameSize);
        m_messageSize = stream.Read<unsigned short>();
        m_message = stream.ReadBytesStr(m_messageSize);

    } catch (std::runtime_error error)
    {

        return false;
    }

    return true;
}
