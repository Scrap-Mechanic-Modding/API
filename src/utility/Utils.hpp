#pragma once

#include <cstdint>
#include <memory>

namespace SMM
{
    namespace Utility
    {

        bool IsCanonical(void* t_address);
        void* AllocCopy(void* t_src, size_t t_size);

        template <typename T>
        union ptr_t
        {
            uintptr_t raw;
            T* ptr;
        };

    } // namespace Utility
} // namespace SMM