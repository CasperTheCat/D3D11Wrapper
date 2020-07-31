#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <atomic>

template<class T>
class CCircularBuffer
{
private:
    std::vector<T> m_buffer;
    std::atomic<size_t> m_start;
    std::atomic<size_t> m_end;
    std::atomic<size_t> m_capacity;
    std::atomic<size_t> m_size;

public:

    size_t size() const 
    {
        // s = &i[start]
        // e = (&i[end] + end)
        // delta = (e - s) % s
        return m_size;
        //return (((m_end + m_capacity) - m_start) % m_capacity);
    };


    size_t capacity() const
    {
        return m_capacity;
    };


    //void push_back(T val);
    void push_back(T val)
    {
        m_buffer[m_end] = val;
        m_end = (m_end + 1) % m_capacity;
        ++m_size;
    };

    void insert(const T* pBuffer, const size_t uSize)
    {
        // Memory Copy
        // Does a single copy suffice?
        size_t dEndContiguous = (m_capacity - m_end);
        
        if(uSize <= dEndContiguous) // Yes, one memcpy works
        {
            memcpy(&m_buffer[m_end], pBuffer, uSize);
            m_end = m_end + (uSize);
        }
        else
        {
            // We have to split the memcpy
            memcpy(&m_buffer[m_end], pBuffer, dEndContiguous * sizeof(T));

            
            // Second
            memcpy(&m_buffer[0], pBuffer + dEndContiguous, (uSize - dEndContiguous) * sizeof(T));
            m_end = 0 + (uSize - dEndContiguous);
        }

        m_size += uSize;

    };

    std::vector<T> dequeue( const size_t uSize)
    {
        auto realSize = uSize;// std::min(uSize, m_size);
        volatile size_t l_Size = m_size;

        if (l_Size < uSize)
        {
            realSize = l_Size;
        }
        
        // Allocate out vector and hope for copy elision
        std::vector<T> outVector;
        outVector.resize(realSize);

        // Memory Copy
        // Does a single copy suffice?
        size_t dDistToEndContiguous = (m_capacity - m_start);

        if (realSize <= dDistToEndContiguous) // Yes, one memcpy works
        {
            memcpy(outVector.data(), &m_buffer[m_start], outVector.size() * sizeof(T));
            m_start = m_start + (realSize);
        }
        else
        {
            // We have to split the memcpy
            memcpy(outVector.data(), &m_buffer[m_start], dDistToEndContiguous * sizeof(T));


            // Second
            memcpy(outVector.data() + dDistToEndContiguous, &m_buffer[0], (realSize - dDistToEndContiguous) * sizeof(T));
            m_start = 0 + (realSize - dDistToEndContiguous);
        }

        m_size -= realSize;

        return outVector;
    };

    bool empty() const noexcept
    {
        return size() == 0;
    };

    bool full() const noexcept
    {
        return size() == capacity();
    };

    size_t reserve() const noexcept
    {
        return capacity() - size();
    };

    void clear() noexcept
    {
        m_start = 0;
        m_end=0;
        m_size=0;
    }

    T& operator[](const size_t index)
    {
        return m_buffer[(m_start + index) % m_capacity];
    };

    void remove(size_t nElements) noexcept
    {
        m_start = (m_start + nElements) % m_capacity;
        m_size -= nElements;
    };

    //T& operator[](size_t index);

    //void insert( );

    CCircularBuffer() : m_start(0), m_end(0),  m_capacity(0), m_size(0)
    {
    };


    explicit CCircularBuffer(size_t uSize) :
        m_buffer(uSize),
        m_start(0),
        m_end(0),
        m_capacity(uSize),
        m_size(0)

    {
        memset(m_buffer.data(), 0xde, m_buffer.size() * sizeof(T));
    };


    ~CCircularBuffer() = default;
};