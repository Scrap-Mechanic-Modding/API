#include "CompressionHelper.hpp"

using namespace SMM::Network;

CompressionHelper* CompressionHelper::s_instance = nullptr;

void CompressionHelper::SetBuffer(char* t_dst, size_t t_maxSize)
{
    m_dstBuffer = t_dst;
    m_dstBufferMax = t_maxSize;
}

int CompressionHelper::Compress(char* t_rawData, size_t t_rawSize)
{
    int result = LZ4_compress_default(t_rawData, m_dstBuffer, int(t_rawSize), int(m_dstBufferMax));
    m_dstBuffer = m_compressionBuf;
    m_dstBufferMax = COMPRESSION_BUFF_SIZE;
    return result;
}

int CompressionHelper::Decompress(char* t_compressedData, size_t t_compressedSize)
{
    int result = LZ4_decompress_safe(t_compressedData, m_dstBuffer, int(t_compressedSize), int(m_dstBufferMax));
    m_dstBuffer = m_compressionBuf;
    m_dstBufferMax = COMPRESSION_BUFF_SIZE;
    return result;
}

CompressionHelper* CompressionHelper::GetInstancePtr()
{
    if (s_instance)
        return s_instance;
    s_instance = new CompressionHelper();
    return s_instance;
}