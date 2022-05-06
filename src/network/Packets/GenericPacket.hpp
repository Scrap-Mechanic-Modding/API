#pragma once

#include "Packet.hpp"
#include "../common.hpp"

namespace SMM
{
    namespace Network
    {

        class GenericPacket : public Packet
        {

        public:
            GenericPacket() :
                Packet(SMM::Network::PacketID::Invalid) {}
            ~GenericPacket() = default;

            virtual size_t GetSize();
            virtual bool Deserialize(char* t_packetData, size_t t_packetSize);
            virtual size_t Serialize(char* t_dst, size_t t_maxDstSize);
            virtual const char* GetName() { return "Unknown Packet"; }
        };

    } // namespace Network
} // namespace SMM