#include "common.hpp"
#include "network/hook.hpp"
#include "utility/InstanceManager.hpp"
#include "utility/ProgramHeader.hpp"

void WINAPI Main()
{
    // auto baseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    auto& instanceMgr = SMM::Utility::InstanceManager::GetInstance();
    const std::string klass = ".?AVCharacter@@";
    std::vector<void*> instances = instanceMgr.GetInstancesByName<void*>(klass);

    printf("Found %llu instance(s) of class '%s'", instances.size(), klass.c_str());
    if (!instances.empty())
    {
        printf(":");
        for (const auto& ptr: instances)
        {
            printf("\n\t- %p", ptr);
        }
    }

    printf("\n");

    // hookNetworkingFuncs(baseAddress);
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
