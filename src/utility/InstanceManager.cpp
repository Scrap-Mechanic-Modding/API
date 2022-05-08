#include "InstanceManager.hpp"

using namespace SMM::Utility;

// TODO: Maybe turn into a template function? would be cleaner to avoid casting every time after calling this
// 4-Byte aligned search
const char* InstanceManager::FindStringInSection(const std::string& t_needle, const std::string& t_section, const ptrdiff_t alignment) const
{
    const auto base_address = reinterpret_cast<char*>(GetModuleHandle(nullptr));
    const IMAGE_SECTION_HEADER* section = m_gameHeader->GetSectionByName(t_section);

    if (!section)
    {
        return nullptr;
    }

    const char* pStart = base_address + section->VirtualAddress;
    const char* pEnd = base_address + section->VirtualAddress + section->Misc.VirtualSize;

    const size_t needle_size = t_needle.size();

    for (auto pCurrent = pStart; pCurrent < pEnd; pCurrent += alignment)
    {
        size_t matched = 0;
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
