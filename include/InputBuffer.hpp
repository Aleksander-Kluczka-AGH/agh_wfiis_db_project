#pragma once

#include "Root.hpp"

/**
 * @brief The class managing buffers for database queries as well as form input fields
 * 
 * @tparam SIZE The size of internal char array, the size must be greater than 0
 */
template <std::size_t SIZE>
requires (SIZE > 0)
class InputBuffer
{
    public:
    /**
     * @brief Default constructor of the Input Buffer object
     */
    InputBuffer();

    /**
     * @brief Constructor filling the buffer
     * 
     * @param content The buffer content to be filled
     */
    InputBuffer(const char* content);

    /**
     * @brief The assignment operator for const char pointers (for ex. string literals)
     * 
     * @param content The buffer content to be filled
     */
    void operator=(const char* content);

    /**
     * @brief The copy assignment operator
     * 
     * @param other The other @c InputBuffer object
     */
    void operator=(const InputBuffer<SIZE>& other);

    /**
     * @brief Explicit conversion dereference operator to the underlying char array
     * 
     * @return The pointer to the first element of the underlying array
     */
    const char* operator*() const;

    /**
     * @brief Implicit conversion operator to mutable underlying array
     * 
     * @return The pointer to the first element of the underlying array
     */
    operator char*();

    /**
     * @brief Implicit conversion operator to immutable underlying array
     * 
     * @return The pointer to the first element of the underlying array
     */
    operator const char*() const;

    /**
     * @brief Implicit conversion operator to the std::string_view
     * 
     * @return The view of the underlying array
     */
    operator std::string_view();

    /**
     * @brief Implicit conversion operator to the const std::string_view
     * 
     * @return The immutable view of the underlying array
     */
    operator const std::string_view() const;

    /**
     * @brief Allows immutable access to any element of the underlying array by index operator
     * 
     * @param index The index of a character in the underlying array
     * @return const char& The const reference to the requested char
     * 
     * @warning This throws when @c index is out of range
     */
    const char& operator[](const std::size_t& index) const;

    /**
     * @brief Allows mutable access to any element of the underlying array by index operator
     * 
     * @param index he index of a character in the underlying array
     * @return The reference to the requested char
     */
    char& operator[](const std::size_t& index);

    /**
     * @brief Gets the underlying array
     * 
     * @return The mutable pointer to the first element of the underlying array
     */
    char* getBuffer();

    /**
     * @brief Gets the underlying array
     * 
     * @return The immutable pointer to the first element of the underlying array
     */
    const char* getBuffer() const;

    /**
     * @brief Gets the total size of the buffer
     * 
     * @return The total size of the buffer
     */
    const std::size_t& size() const;

    /**
     * @brief Gets the length of the currently stored string
     * 
     * @return The length of the currently stored string
     */
    std::size_t length() const;  // gets the length of the string in the buffer

    //convenience methods

    /**
     * @brief Explicit conversion from C string to integer
     * 
     * @return The integer representation of string contents
     * 
     * Internally this uses std::atoi
     */
    int toInt() const;

    /**
     * @brief Explicit conversion from C string to bool
     * 
     * @return The bool representation of string contents
     */
    bool toBoolean() const;

    /**
     * @brief Explicit conversion from C string to std::string
     * 
     * @return The std::string representation of string contents
     */
    std::string toString() const;

    private:
    const std::size_t m_size; // The total size of the buffer
    char m_buffer[SIZE]; // The buffer
};

#include "../src/InputBuffer.inl"
