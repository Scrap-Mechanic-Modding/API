#pragma once

#include "../common.hpp"
#include "ProgramHeader.hpp"
#include "Utils.hpp"

#include <memory>
#include <unordered_map>
#include <windows.h>

namespace SMM
{
    namespace Utility
    {

        struct RTTICompleteObjectLocator {
            int signature;
            int offset;
            int cdOffset;
            uint32_t typeDescriptor;
            uint32_t classDescriptor;
            uint32_t objectBase;
        };

        struct RTTITypeDescriptor {
            void* type_info_vftable;
            uint64_t spare;
            char type_name[1];
        };

        class InstanceManager
        {
        public:
            InstanceManager(InstanceManager const&) = delete;
            void operator=(InstanceManager const&) = delete;

            template<class T>
            std::vector<T> GetInstancesByName(const std::string& t_name)
            {
                std::vector<T> result = {};

                ptr_t<void> vftable_ptr;
                vftable_ptr.ptr = m_mapVftables[t_name.c_str()];

                if (vftable_ptr.ptr == nullptr)
                    return result;

                HANDLE handles[100];
                const unsigned int num_heaps = GetProcessHeaps(sizeof(handles) / sizeof(HANDLE), handles);

                for (unsigned int i = 0; i < num_heaps; i++)
                {
                    HANDLE current_heap = handles[i];

                    PROCESS_HEAP_ENTRY entry;
                    entry.lpData = NULL;

                    if (!HeapLock(current_heap))
                        continue;

                    while (HeapWalk(current_heap, &entry))
                    {
                        if ((entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) == 0)
                            continue;

                        ptr_t<uintptr_t> pStart;
                        pStart.ptr = static_cast<uintptr_t*>(entry.lpData);

                        const ptr_t<uintptr_t> pEnd{pStart.raw + entry.cbData};

                        for (auto pCurrent = pStart; pCurrent.ptr < pEnd.ptr; pCurrent.ptr++)
                        {
                            if (*pCurrent.ptr == vftable_ptr.raw)
                                result.push_back(reinterpret_cast<T*>(pCurrent.raw));
                        }
                    }

                    HeapUnlock(current_heap);
                }

                return result;
            }

            static InstanceManager& GetInstance()
            {
                static InstanceManager s_instance;
                return s_instance;
            }

        private:
            std::unordered_map<std::string, void*> m_mapVftables;
            std::unordered_map<std::string, void*> m_mapRTTILocators;
            std::unique_ptr<ProgramHeader> m_gameHeader;

            const char* FindStringInSection(const std::string& t_needle, const std::string& t_section, const ptrdiff_t alignment = 4) const;
            std::unordered_map<std::string, void*> FindVFTables() const;

            InstanceManager()
            {
                ptr_t<void> base_address;
                base_address.ptr = GetModuleHandle(nullptr);

                // Setup ProgramHeader for current process (scrap mechanic)
                m_gameHeader = std::make_unique<ProgramHeader>(base_address);

                m_mapVftables = FindVFTables();
                printf("Found %llu VFTables\n", m_mapVftables.size());
                printf("std::shared_ptr<LuaManager> = %p\n", m_mapVftables[".?AV?$_Ref_count_resource@PEAVLuaManager@@P6AXPEAV1@@Z@std@@"]);

                // TODO: Generate additional metadata for each class (#funcs, hierarchy, size?)
            }
        };
    } // namespace Utility
} // namespace SMM
