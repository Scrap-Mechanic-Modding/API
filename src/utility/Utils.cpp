#include "Utils.hpp"

using namespace SMM;

bool Utility::IsCanonical(void* t_address)
{
    uintptr_t numeric_address = reinterpret_cast<uintptr_t>(t_address);
    return (numeric_address & 0x00007FFFFFFFFFFFULL) == numeric_address;
}

void* Utility::AllocCopy(void* t_src, size_t t_size)
{
    void* new_data = malloc(t_size);
    if (new_data == NULL)
    {
        return nullptr;
    }
    memcpy(new_data, t_src, t_size);
    return new_data;
}
