#include "InstanceManager.hpp"

using namespace SMM::Utility;

// TODO: Maybe turn into a template function? would be cleaner to avoid casting every time after calling this
// 4-Byte aligned search
char* InstanceManager::FindStringInSection(const std::string& t_needle, const std::string& t_section)
{
    auto base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
    IMAGE_SECTION_HEADER* section = m_gameHeader->GetSectionByName(t_section);
    printf("Section: %p\n", section);
    if (!section)
    {
        return nullptr;
    }

    auto pStart = reinterpret_cast<char*>(base_address + section->VirtualAddress);
    auto pEnd = reinterpret_cast<char*>(base_address + section->VirtualAddress + section->Misc.VirtualSize);

    printf("Searching range: %p -> %p\n", pStart, pEnd);

    auto needle_size = t_needle.size();

    for (auto pCurrent = pStart; pCurrent < pEnd; pCurrent += 4)
    {
        int matched = 0;
        while (matched < needle_size)
        {
            if (pCurrent[matched] != t_needle[matched])
                break;

            matched++;
        }

        // If needle was found, return it
        if (matched == needle_size)
        {
            return pCurrent;
        }
    }

    return nullptr;
}
