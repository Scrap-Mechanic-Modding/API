#pragma once

#include "Utils.hpp"

namespace SMM
{
    namespace Utility
    {

        class VMTHook
        {
            size_t m_countFuncs = SIZE_MAX;
            void*** m_tablePtr;

            void** m_hookedTable;
            void** m_originalTable;

        public:
            VMTHook(void*** vtable_ptr) :
                m_tablePtr(vtable_ptr), m_originalTable(*vtable_ptr)
            {
                // Roughly count amount of plausible consecutive pointers
                while (IsCanonical(m_originalTable[++m_countFuncs])) {}

                // Grab a snapshot for hooking
                m_hookedTable = static_cast<void**>(AllocCopy(m_originalTable, m_countFuncs * sizeof(void*)));
                // todo: assert pointer is not null
            }

            ~VMTHook()
            {
                if (IsEnabled())
                    Disable();
                delete[] m_hookedTable;
            }

            inline void Hook(void* new_func, size_t index)
            {
                if (index < m_countFuncs)
                    m_hookedTable[index] = new_func;
            }

            inline void Unhook(size_t index)
            {
                if (index < m_countFuncs)
                    m_hookedTable[index] = m_originalTable[index];
            }

            inline void* GetCurrentFuncPtr(size_t index)
            {
                if (index >= m_countFuncs)
                    return nullptr;
                return (*m_tablePtr)[index];
            }

            inline void* GetHookedFuncPtr(size_t index)
            {
                if (index >= m_countFuncs)
                    return nullptr;
                return m_hookedTable[index];
            }

            inline void* GetOriginalFuncPtr(size_t index)
            {
                if (index >= m_countFuncs)
                    return nullptr;
                return m_originalTable[index];
            }

            inline bool IsEnabled()
            {
                return *m_tablePtr == m_hookedTable;
            }

            inline void Enable()
            {
                if (!IsEnabled())
                    *m_tablePtr = m_hookedTable;
            }

            inline void Disable()
            {
                if (IsEnabled())
                    *m_tablePtr = m_originalTable;
            }
        };

    } // namespace Utility
} // namespace SMM