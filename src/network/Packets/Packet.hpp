#pragma once

#include "../../common.hpp"


namespace SMM
{
    namespace Network
    {

        enum class PacketID
        {
            Invalid = 0,
            C2S_ChatPacket = 28,
            S2C_ChatPacket = 29
        };

        class Packet
        {

        public:
            PacketID m_id;

            Packet(PacketID t_packetID = PacketID::Invalid) :
                m_id(t_packetID) {}
            ~Packet() = default;

            virtual size_t GetSize() = 0;
            virtual bool Deserialize(char* t_packetData, size_t t_packetSize) = 0;
            virtual size_t Serialize(char* t_dst, size_t t_maxDstSize) = 0;
            virtual const char* GetName() = 0;
        };

    } // namespace Network
} // namespace SMM