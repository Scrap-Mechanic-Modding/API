#pragma once

#include "../common.hpp"
#include "Packet.hpp"

#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>

namespace SMM
{
    namespace Network
    {

        class C2S_ChatPacket : public Packet
        {

        public:
            C2S_ChatPacket() :
                Packet(PacketID::C2S_ChatPacket) {}
            ~C2S_ChatPacket() = default;

            unsigned int m_databaseID{0};
            unsigned short m_channelID{0};
            unsigned char m_worldID{0};
            unsigned int m_flags{0};
            unsigned int m_mystery{0}; // unknown 4-byte sequence, possibly a checksum
            char m_mystery2[3];        //unknown 3-byte sequence
            time_t m_timestamp{0};
            unsigned short m_playerNameSize{0};
            std::string m_playerName{""};
            unsigned short m_messageSize{0};
            std::string m_message{""};

            virtual size_t GetSize();
            virtual bool Deserialize(char* t_packetData, size_t t_packetSize);
            virtual size_t Serialize(char* t_dst, size_t t_maxDstSize);
            virtual const char* GetName() { return "C2S_ChatPacket"; }
        };

    } // namespace Network
} // namespace SMM