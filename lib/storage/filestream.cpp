#include "filestream.hpp"

#include <sstream>

#ifdef ESP_PLATFORM
#include <SD.h>
#endif

namespace storage
{

    FileStream::FileStream() {}

    FileStream::FileStream(const std::string& path, Mode mode)
    {
        this->open(path, mode);
    }

    FileStream::~FileStream()
    {
        m_stream.close();
    }

    void FileStream::open(const std::string& path, Mode mode)
    {
        if (mode == READ)
            m_stream.open(path, std::ios::in | std::ios::binary);
        else if (mode == WRITE)
            m_stream.open(path, std::ios::out | std::ios::binary);
        else if (mode == APPEND)
            m_stream.open(path, std::ios::app | std::ios::binary);
    }

    void FileStream::close(void)
    {
        m_stream.close();
    }

    std::string FileStream::read(size_t returnSize)
    {
        if (returnSize == -1)
        {
            std::stringstream buffer;
            buffer << m_stream.rdbuf();
            return buffer.str();
        }
        else
        {
            // Resize the string to accommodate `returnSize` bytes
            std::string buff;
            buff.resize(returnSize);

            // Read from the stream into the buffer
            m_stream.read(&buff[0], returnSize); // Safe access to underlying data

            // Shrink the string to the actual number of bytes read (gcount())
            buff.resize(m_stream.gcount());

            return buff;
        }
    }

    std::string FileStream::readline(void)
    {
        std::string line;
        std::getline(m_stream, line);
        return line;
    }

    std::string FileStream::readword(void)
    {
        std::string word;
        m_stream >> word;
        return word;
    }

    std::size_t FileStream::read(char* buffer, std::size_t len)
    {
        m_stream.read(buffer, len);
        return m_stream.gcount(); // Returns the number of characters read
    }

    char FileStream::readchar(void)
    {
        return m_stream.get();
    }

    void FileStream::write(const std::string& str)
    {
        m_stream << str;
    }

    void FileStream::write(const char* str, std::size_t len)
    {
        m_stream.write(str, len);
    }

    void FileStream::write(const char c)
    {
        m_stream << c;
    }

    bool FileStream::isopen(void) const
    {
        return m_stream.is_open();
    }

    long FileStream::size(void)
    {
        const auto position = m_stream.tellg();
        m_stream.seekg(0, std::ios::beg);
        const auto begin = m_stream.tellg();
        m_stream.seekg(0, std::ios::end);
        const auto end = m_stream.tellg();
        const auto fsize = (end - begin);
        m_stream.seekg(position);
        return fsize;
    }

    long FileStream::sizeFromCurrentPosition(void)
    {
        const auto currentPosition = m_stream.tellg();
        m_stream.seekg(0, std::ios::end);
        const auto end = m_stream.tellg();
        const auto fsize = (end - currentPosition);
        m_stream.seekg(currentPosition);
        return fsize;
    }

    FileStream& operator<<(FileStream& stream, const std::string& text)
    {
        stream.write(text);
        return stream;
    }

    FileStream& operator>>(FileStream& stream, std::string& buff)
    {
        buff = stream.readword();
        return stream;
    }

} // namespace storage
