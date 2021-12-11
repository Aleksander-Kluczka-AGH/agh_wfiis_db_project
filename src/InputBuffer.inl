template <std::size_t SIZE>
InputBuffer<SIZE>::InputBuffer()
:
m_size(SIZE),
m_buffer("")
{ }

template <std::size_t SIZE>
const char* InputBuffer<SIZE>::operator*() const
{
    return m_buffer;
}

template <std::size_t SIZE>
InputBuffer<SIZE>::operator char*()
{
    return m_buffer;
}

template <std::size_t SIZE>
InputBuffer<SIZE>::operator const char*() const
{
    return m_buffer;
}

template <std::size_t SIZE>
InputBuffer<SIZE>::operator std::string_view()
{
    return std::string_view(m_buffer);
}

template <std::size_t SIZE>
InputBuffer<SIZE>::operator const std::string_view() const
{
    return std::string_view(m_buffer);
}

template <std::size_t SIZE>
const char& InputBuffer<SIZE>::operator[](const std::size_t& index) const
{
    if(index < SIZE)
    {
        return m_buffer[index];
    }
    else
    {
        throw std::out_of_range("Index "+std::to_string(index)+" is out of range of size "+std::to_string(SIZE)+".");
    }
}

template <std::size_t SIZE>
char& InputBuffer<SIZE>::operator[](const std::size_t& index)
{
    if(index < SIZE)
    {
        return m_buffer[index];
    }
    else
    {
        throw std::out_of_range("Index "+std::to_string(index)+" is out of range of size "+std::to_string(SIZE)+".");
    }
}

template <std::size_t SIZE>
int InputBuffer<SIZE>::toInt() const
{
    return std::atoi(m_buffer);
}

template <std::size_t SIZE>
bool InputBuffer<SIZE>::toBoolean() const
{
    std::string_view sv(m_buffer);
    if(sv.find("yes")
    || sv.find("Yes")
    || this->toInt()
    || sv.find("true")
    || sv.find("True"))
    {
        return true;
    }
    else
    {
        return false;
    }
}