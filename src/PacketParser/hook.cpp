#include "PacketParser.hpp"
#include "Utils.hpp"
#include "VMT.hpp"
#include "common.hpp"
#include "hook.hpp"

#include <memory>

#define STEAM_NETSOCK_INTERFACE_FUNC_OFFSET 0xdb5c00

std::unique_ptr<SMM::Utility::VMTHook> SteamNetSockInterfaceHook = nullptr;

size_t hk_ReceiveMessagesOnPollGroup(void* self, void* poll_group, SteamNetworkingMessage_t** out_msg, size_t msg_max)
{
    static auto o_ReceiveMessagesOnPollGroup = static_cast<decltype(hk_ReceiveMessagesOnPollGroup)*>(SteamNetSockInterfaceHook->GetOriginalFuncPtr(14));

    return o_ReceiveMessagesOnPollGroup(self, poll_group, out_msg, msg_max);
}

size_t hk_SendMessageToConnection(void* self, int h_conn, void* buff, size_t size, int flag, int64* out_msg_num)
{
    static auto o_SendMessageToConnection = static_cast<decltype(hk_SendMessageToConnection)*>(SteamNetSockInterfaceHook->GetOriginalFuncPtr(11));

    return o_SendMessageToConnection(self, h_conn, buff, size, flag, out_msg_num);
}

int hookNetworkingFuncs(char* baseAddress)
{
    auto SteamNetSockInterface = static_cast<void****>(SteamInternal_ContextInit(baseAddress + STEAM_NETSOCK_INTERFACE_FUNC_OFFSET));

    SteamNetSockInterfaceHook = std::make_unique<SMM::Utility::VMTHook>(*SteamNetSockInterface);
    SteamNetSockInterfaceHook->Hook(&hk_ReceiveMessagesOnPollGroup, 14);
    SteamNetSockInterfaceHook->Hook(&hk_SendMessageToConnection, 11);
    SteamNetSockInterfaceHook->Enable();

    return 0;
}