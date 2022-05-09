#pragma once

#include "../common.hpp"
#include "ProgramHeader.hpp"

#include <memory>
#include <unordered_map>

namespace SMM
{
    namespace Utility
    {
        class InstanceManager
        {
        public:
            InstanceManager(InstanceManager const&) = delete;
            void operator=(InstanceManager const&) = delete;

            template<class T>
            std::vector<T> GetInstancesByName(std::string& t_name)
            {
                // TODO: Magic
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
                // Setup ProgramHeader for current process (scrap mechanic)
                auto base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
                m_gameHeader = std::make_unique<ProgramHeader>(base_address);
                m_mapVftables = FindVFTables();
                printf("Found %llu VFTables\n", m_mapVftables.size());
                printf("std::shared_ptr<LuaManager> = %p\n", m_mapVftables[".?AV?$_Ref_count_resource@PEAVLuaManager@@P6AXPEAV1@@Z@std@@"]);

                // TODO: Generate additional metadata for each class (#funcs, hierarchy, size?)
            }
        };
    } // namespace Utility
} // namespace SMM
