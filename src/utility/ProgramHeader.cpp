#include "ProgramHeader.hpp"

using namespace SMM::Utility;

ProgramHeader::ProgramHeader(ptr_t<void> t_baseAddress)
{
    m_dosHeader.raw = t_baseAddress.raw;
    m_ntHeaders.raw = t_baseAddress.raw + m_dosHeader.ptr->e_lfanew;
    m_sectionHeaders.raw = ((uintptr_t) &m_ntHeaders.ptr->OptionalHeader + m_ntHeaders.ptr->FileHeader.SizeOfOptionalHeader);

    for (int i = 0; i < m_ntHeaders.ptr->FileHeader.NumberOfSections; i++)
    {
        std::string sectionName((char*) &m_sectionHeaders.ptr[i].Name, 8);
        m_sections[sectionName.c_str()] = &m_sectionHeaders.ptr[i];
    }
}
