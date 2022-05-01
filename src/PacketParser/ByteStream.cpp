#include "ByteStream.hpp"

using namespace SMM::Network;

ByteStream::ByteStream(char* t_buffer, size_t t_size) :
    m_bufferStart(t_buffer), m_bufferEnd(t_buffer + t_size), m_current(t_buffer)
{
}

void ByteStream::Skip(size_t t_size)
{
    if (m_current + t_size > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to skip");
    }

    m_current += t_size;
}

std::vector<char> ByteStream::ReadBytesVec(size_t t_size)
{
    if (m_current + t_size > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to create vector");
    }

    std::vector<char> vec(m_current, m_current + t_size);
    m_current += t_size;

    return vec;
}

std::string ByteStream::ReadBytesStr(size_t t_size)
{
    if (m_current + t_size > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to create string");
    }

    std::string str(m_current, t_size);
    m_current += t_size;

    return str;
}

void ByteStream::WriteBytesVec(std::vector<char>& vec)
{
    if (m_current + vec.size() > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to write vector");
    }

    if (vec.size() == 0)
    {
        throw std::runtime_error("Vector size cannot be zero");
    }

    memcpy(m_current, vec.data(), vec.size());
    m_current += vec.size();
}

void ByteStream::WriteBytesStr(std::string& str)
{
    if (m_current + str.size() > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to write string");
    }

    memcpy(m_current, str.data(), str.size());
    m_current += str.size();
}

void ByteStream::WriteByte(char byte, size_t t_quantity)
{
    if (m_current + t_quantity > m_bufferEnd)
    {
        throw std::range_error("Not enough space in buffer to write bytes");
    }

    memset(m_current, byte, t_quantity);

    m_current += t_quantity;
}