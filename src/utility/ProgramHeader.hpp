#include <winnt.h>

class ProgramHeader
{
public:
	void* m_base;

	uint16_t* m_dosMagic;
	
	//58 bytes
	
	uint32_t* m_peLoc;

	uint32_t* m_peSignature;
	uint16_t* m_machine;
	uint16_t* m_numSections;
	uint32_t* m_timeStamp;
	uint32_t* m_symbolTableOffset;
	uint32_t* m_numOfSymbols;
	uint16_t* m_sizeOfOptHeader;
	uint16_t* m_char;

};