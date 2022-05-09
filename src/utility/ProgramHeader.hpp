#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Utils.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <windows.h>

namespace SMM
{
    namespace Utility
    {

        class ProgramHeader
        {
        private:
            ptr_t<IMAGE_DOS_HEADER> m_dosHeader;
            // DOS Stub
            ptr_t<IMAGE_NT_HEADERS64> m_ntHeaders;
            ptr_t<IMAGE_SECTION_HEADER> m_sectionHeaders;

            std::unordered_map<std::string, IMAGE_SECTION_HEADER*> m_sections;

        public:
            ProgramHeader(ptr_t<void> t_baseAddress);

            inline IMAGE_SECTION_HEADER* GetSectionByName(const std::string& t_name)
            {
                return m_sections[t_name.c_str()];
            }
        };

    } // namespace Utility
} // namespace SMM
