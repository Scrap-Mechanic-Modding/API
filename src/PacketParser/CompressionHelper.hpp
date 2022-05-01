#pragma once

#include "Utils.hpp"
#include "lz4/lz4.h"

namespace SMM
{
    namespace Network
    {

        class CompressionHelper
        {

        private:
            static CompressionHelper* s_instance;
            static constexpr int COMPRESSION_BUFF_SIZE = 0x80000;
            char* m_compressionBuf{new char[COMPRESSION_BUFF_SIZE]};

            char* m_dstBuffer{m_compressionBuf};
            size_t m_dstBufferMax{COMPRESSION_BUFF_SIZE};

            CompressionHelper() = default;

        public:
            void SetBuffer(char* t_dst, size_t t_maxSize);
            int Decompress(char* t_compressedData, size_t t_compressedSize);
            int Compress(char* t_rawData, size_t t_rawSize);

            inline char* GetGlobalBuffer() { return m_compressionBuf; }
            inline size_t GetGlobalBufferSize() { return m_dstBufferMax; }

            static CompressionHelper* GetInstancePtr();
        };

    } // namespace Network
} // namespace SMM