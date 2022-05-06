#pragma once

namespace SMM
{
    namespace Utility
    {

        bool IsCanonical(void* t_address);
        void* AllocCopy(void* t_src, size_t t_size);
        
    } // namespace Utility
} // namespace SMM