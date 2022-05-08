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
            std::unordered_map<std::string, void*> m_vtables;
            std::unique_ptr<ProgramHeader> m_gameHeader;

            char* FindStringInSection(const std::string& t_needle, const std::string& t_section);

            InstanceManager()
            {
                // Setup ProgramHeader for current process (scrap mechanic)
                auto base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(NULL));
                m_gameHeader = std::make_unique<ProgramHeader>(base_address);

                // Find ".?AVtype_info@@" from the .rdata section
                char* str_type_info = FindStringInSection(".?AVtype_info@@", ".data");

                printf("[InstanceManager] Found: %s\n", str_type_info);
                // TODO: Cross-reference for type_info's address to get type descriptor
                // type descriptor -> complete locator -> vtable -> all rtti locators
            }
        };
    } // namespace Utility
} // namespace SMM
