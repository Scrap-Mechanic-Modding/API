#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>
#include <unordered_map>

namespace SMM
{
    namespace Utility
    {

        class ProgramHeader
        {
        public:
            IMAGE_DOS_HEADER* m_dosHeader;
            //DOS Stub
            IMAGE_NT_HEADERS64* m_ntHeaders;
            IMAGE_SECTION_HEADER* m_sectionHeaders;

            short m_numOfSections;

            std::unordered_map<std::string, IMAGE_SECTION_HEADER*> m_sections;

            ProgramHeader(uintptr_t t_baseAddress);
        };

    } // namespace Utility
} // namespace SMM