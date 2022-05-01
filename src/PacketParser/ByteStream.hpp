#pragma once

#include <stdexcept>
#include <string>
#include <vector>

namespace SMM
{
    namespace Network
    {

        class ByteStream
        {

        private:
            char* m_bufferStart;
            char* m_bufferEnd;

            char* m_current;

        public:
            ByteStream(char* t_buffer, size_t t_size);

            template<typename T>
            T Read()
            {
                if (m_current + sizeof(T) > m_bufferEnd)
                {
                    throw std::range_error("Not enough space in buffer to read type");
                }

                T* val = (T*) m_current;
                m_current += sizeof(T);

                return *val;
            }

            std::vector<char> ReadBytesVec(size_t t_size);
            std::string ReadBytesStr(size_t t_size);

            template<typename T>
            void Write(T& t_val)
            {
                if (m_current + sizeof(T) > m_bufferEnd)
                {
                    throw std::range_error("Not enough space in buffer to write type");
                }

                memcpy(m_current, &t_val, sizeof(T));
                m_current += sizeof(T);
            }

            void WriteBytesVec(std::vector<char>& vec);
            void WriteBytesStr(std::string& str);
            void WriteByte(char t_byte, size_t t_quantity);

            void Skip(size_t t_size);
        };

    } // namespace Network
} // namespace SMM