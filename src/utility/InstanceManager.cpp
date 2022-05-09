#include "InstanceManager.hpp"
#include "Utils.hpp"

#include <Windows.h>

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

template<class T>
union ptr_t {
    uintptr_t uint;
    T* ptr;
    char* cptr;
};

struct _RTTICompleteObjectLocator {
    int signature;
    int offset;
    int cdOffset;
    uint32_t typeDescriptor;
    uint32_t classDescriptor;
    uint32_t objectBase;
};

struct _RTTITypeDescriptor {
    void* type_info_vftable;
    uint64_t spare;
    char type_name[1];
};

std::unordered_map<std::string, void*> InstanceManager::FindVFTables() const
{
    std::unordered_map<std::string, void*> results;

    ptr_t<HINSTANCE__> base_address;
    base_address.ptr = GetModuleHandle(nullptr);

    const PIMAGE_SECTION_HEADER section_rdata = m_gameHeader->GetSectionByName(".rdata");
    const PIMAGE_SECTION_HEADER section_text = m_gameHeader->GetSectionByName(".text");

    if (!section_rdata)
        return {};

    const ptr_t<uintptr_t> pStart_rdata{base_address.uint + section_rdata->VirtualAddress};
    const ptr_t<uintptr_t> pEnd_rdata{base_address.uint + section_rdata->VirtualAddress + section_rdata->SizeOfRawData};

    const ptr_t<uintptr_t> pStart_text{base_address.uint + section_text->VirtualAddress};
    const ptr_t<uintptr_t> pEnd_text{base_address.uint + section_text->VirtualAddress + section_text->SizeOfRawData};

    for (auto pCurrent = pStart_rdata; pCurrent.ptr < pEnd_rdata.ptr; pCurrent.ptr++)
    {
        const ptr_t<uintptr_t> current_data{*pCurrent.ptr};

        if (!IsCanonical(current_data.ptr) || current_data.ptr < pStart_text.ptr || current_data.ptr > pEnd_text.ptr)
            continue;

        const ptr_t<_RTTICompleteObjectLocator> rtti_ptr{*(pCurrent.ptr - 1)};

        if (!IsCanonical(rtti_ptr.cptr) || rtti_ptr.uint < pStart_rdata.uint || rtti_ptr.uint > pEnd_rdata.uint)
            continue;

        if (rtti_ptr.uint != rtti_ptr.ptr->objectBase + base_address.uint)
            continue;

        const ptr_t<_RTTITypeDescriptor> type_descriptor{rtti_ptr.ptr->typeDescriptor + base_address.uint};
        results[type_descriptor.ptr->type_name] = pCurrent.ptr;
    }

    return results;
}
