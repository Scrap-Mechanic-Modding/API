#include "InstanceManager.hpp"
#include "Utils.hpp"

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

std::unordered_map<std::string, void*> InstanceManager::FindVFTables() const
{
    std::unordered_map<std::string, void*> results;

    ptr_t<HINSTANCE__> base_address;
    base_address.ptr = GetModuleHandle(nullptr);

    const PIMAGE_SECTION_HEADER section_rdata = m_gameHeader->GetSectionByName(".rdata");
    const PIMAGE_SECTION_HEADER section_text = m_gameHeader->GetSectionByName(".text");

    if (!section_rdata)
        return {};

    const ptr_t<uintptr_t> pStart_rdata{base_address.raw + section_rdata->VirtualAddress};
    const ptr_t<uintptr_t> pEnd_rdata{base_address.raw + section_rdata->VirtualAddress + section_rdata->SizeOfRawData};

    const ptr_t<uintptr_t> pStart_text{base_address.raw + section_text->VirtualAddress};
    const ptr_t<uintptr_t> pEnd_text{base_address.raw + section_text->VirtualAddress + section_text->SizeOfRawData};

    for (auto pCurrent = pStart_rdata; pCurrent.ptr < pEnd_rdata.ptr; pCurrent.ptr++)
    {
        const ptr_t<RTTICompleteObjectLocator> rtti_ptr{*pCurrent.ptr};
        if (!IsCanonical(rtti_ptr.ptr) || rtti_ptr.raw < pStart_rdata.raw || rtti_ptr.raw > pEnd_rdata.raw)
            continue;

        const ptr_t<uintptr_t> vftable_start{*(pCurrent.ptr + 1)};
        if (!IsCanonical(vftable_start.ptr) || vftable_start.raw < pStart_text.raw || vftable_start.raw > pEnd_text.raw)
            continue;

        if (rtti_ptr.raw != rtti_ptr.ptr->objectBase + base_address.raw)
            continue;

        // Save to results
        const ptr_t<RTTITypeDescriptor> type_descriptor{rtti_ptr.ptr->typeDescriptor + base_address.raw};
        results[type_descriptor.ptr->type_name] = pCurrent.ptr;

        int num_vfuncs = 0;
        do
        {
            const ptr_t<uintptr_t> vftable_func{*(pCurrent.ptr + 1)};
            if (!IsCanonical(vftable_func.ptr) || vftable_func.raw < pStart_text.raw || vftable_func.raw > pEnd_text.raw)
                break;

            pCurrent.ptr++;
            num_vfuncs++;
        } while (true);
    }

    return results;
}
