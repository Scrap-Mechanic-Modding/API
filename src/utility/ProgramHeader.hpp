#pragma once

#define WIN32_LEAN_AND_MEAN

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
            IMAGE_DOS_HEADER* m_dosHeader;
            // DOS Stub
            IMAGE_NT_HEADERS64* m_ntHeaders;
            IMAGE_SECTION_HEADER* m_sectionHeaders;

            short m_numOfSections;

            std::unordered_map<std::string, IMAGE_SECTION_HEADER*> m_sections;

        public:
            ProgramHeader(uintptr_t t_baseAddress);

            inline IMAGE_SECTION_HEADER* GetSectionByName(const std::string& t_name)
            {
                return m_sections[t_name.c_str()];
            }
        };

    } // namespace Utility
} // namespace SMM
