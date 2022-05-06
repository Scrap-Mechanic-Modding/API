#pragma once

#include "Packets/Packet.hpp"

#include <unordered_map>
#include <vector>

namespace SMM
{
    namespace Network
    {

        typedef Packet* (*packet_cb_t)(Packet*);

        class PacketParser
        {

        private:
            std::unordered_map<std::string, std::vector<packet_cb_t>> m_events;

        public:
            enum class CB_Action : uint8_t
            {
                Pass,
                Modify,
                Drop
            };

            PacketParser();
            ~PacketParser();

            Packet* Process(void* t_data, size_t t_size);
            CB_Action ForwardTo(std::string& t_eventName, Packet* t_packet);

            int BindCallback(
                int t_packetID,
                packet_cb_t t_funcPtr,
                bool t_shouldBeValidation);

            bool UnbindCallback(int t_identifer);
        };

    } // namespace Network
} // namespace SMM