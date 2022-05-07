#include "ProgramHeader.hpp"

using namespace SMM::Utility;

ProgramHeader::ProgramHeader(uintptr_t t_baseAddress)
{
    m_dosHeader = (IMAGE_DOS_HEADER*) t_baseAddress;
    m_ntHeaders = (IMAGE_NT_HEADERS64*) (t_baseAddress + m_dosHeader->e_lfanew);
    m_sectionHeaders = (IMAGE_SECTION_HEADER*) (&m_ntHeaders->OptionalHeader + m_ntHeaders->FileHeader.SizeOfOptionalHeader);
    m_numOfSections = m_ntHeaders->FileHeader.NumberOfSections;

    std::string sectionName;

    for (int i = 0; i <= m_numOfSections; ++i)
    {
    	sectionName = std::string((char*) &m_sectionHeaders[i].Name, 8);
        m_sections[sectionName] = &m_sectionHeaders[i];
    }
}
