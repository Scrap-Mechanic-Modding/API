#include "common.hpp"
#include "network/hook.hpp"
#include "utility/InstanceManager.hpp"
#include "utility/ProgramHeader.hpp"

#include <process.h>
#include <stdio.h>

void WINAPI Main()
{
    auto baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    SMM::Utility::InstanceManager::GetInstance();
    
    hookNetworkingFuncs(baseAddress);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, PVOID lpReserved)
{

    UNUSED(lpReserved);

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(Main), NULL, NULL, NULL);
            break;

        case DLL_PROCESS_DETACH:

            break;
    }
    return TRUE;
}
