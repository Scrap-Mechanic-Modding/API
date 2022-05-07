#include "common.hpp"
#include "hook.hpp"

#include <process.h>

void WINAPI Main()
{
    auto baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
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