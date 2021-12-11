#pragma once

#include "Root.hpp"

template <std::size_t SIZE>
requires (SIZE > 0)
class InputBuffer
{
    public:
    InputBuffer();

    const char* operator*() const;
    operator char*();
    operator const char*() const;
    operator std::string_view();
    operator const std::string_view() const;
    const char& operator[](const std::size_t& index) const;
    char& operator[](const std::size_t& index);

    //convenience methods
    int toInt() const;
    bool toBoolean() const;

    private:
    const std::size_t m_size;
    char m_buffer[SIZE];
};

#include "../src/InputBuffer.inl"