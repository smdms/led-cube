#ifndef CUBE_H
#define CUBE_H

#include "range.h"
#include "layer.h"
#include "coordinates.h"

template <int N>
class Cube
{
public:
    Cube();
    Cube(const bool (&value)[N][N][N]);

    // parallel to pcb; starts from bottom
    Layer<N> xLayer(const int index);

    // parallel to pins; starts from 0-13 side
    Layer<N> yLayer(const int index);

    // parallel to resistors; starts from 0/A5 side
    Layer<N> zLayer(const int index);

    bool& at(const Coordinates& c);

    // operator[] returns xLayer
    Layer<N> operator[](const int index);
    Cube& operator=(const Cube& other);
    Cube& operator=(const bool value);

    Cube& operator|(const Cube& other);

private:
    bool _elements[N][N][N];
};

//

template <int N>
Cube<N>::Cube()
: _elements{}
{}

template <int N>
Cube<N>::Cube(const bool (&value)[N][N][N])
: _elements{}
{
    for (const auto l : range(N))
    {
        for (const auto r : range(N))
        {
            for (const auto c : range(N))
            {
                _elements[l][r][c] = value[l][r][c];
            }
        }
    }
}

template <int N>
Layer<N> Cube<N>::xLayer(const int index)
{
    bool *initializer[N][N]{};
    for (const auto r : range(N))
    {
        for (const auto c : range(N))
        {
            initializer[r][c] = &(_elements[index][r][c]);
        }
    }
    return Layer<N>(initializer);
}

template <int N>
Layer<N> Cube<N>::yLayer(const int index)
{
    bool *initializer[N][N]{};
    for (const auto r : range(N))
    {
        for (const auto c : range(N))
        {
            initializer[r][c] = &(_elements[r][index][c]);
        }
    }
    return Layer<N>(initializer);
}

template <int N>
Layer<N> Cube<N>::zLayer(const int index)
{
    bool *initializer[N][N]{};
    for (const auto r : range(N))
    {
        for (const auto c : range(N))
        {
            initializer[r][c] = &(_elements[r][c][index]);
        }
    }
    return Layer<N>(initializer);
}

template <int N>
bool& Cube<N>::at(const Coordinates& c)
{
    return this->operator[](c.x)[c.y][c.z];
}

template <int N>
Layer<N> Cube<N>::operator[](const int index)
{
    return xLayer(index);
}

template <int N>
Cube<N>& Cube<N>::operator=(const Cube& other)
{
    for (const auto l : range(N))
    {
        for (const auto r : range(N))
        {
            for (const auto c : range(N))
            {
                _elements[l][r][c] = other._elements[l][r][c];
            }
        }
    }
    return *this;
}

template <int N>
Cube<N>& Cube<N>::operator=(const bool value)
{
    for (const auto l : range(N))
    {
        for (const auto r : range(N))
        {
            for (const auto c : range(N))
            {
                _elements[l][r][c] = value;
            }
        }
    }
    return *this;
}

template <int N>
Cube<N>& Cube<N>::operator|(const Cube& other)
{
    for (const auto l : range(N))
    {
        for (const auto r : range(N))
        {
            for (const auto c : range(N))
            {
                _elements[l][r][c] |= other._elements[l][r][c];
            }
        }
    }
    return *this;
}

#endif