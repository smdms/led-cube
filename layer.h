#ifndef LAYER_H
#define LAYER_H

#include "range.h"
#include "row.h"

template <int N>
class Layer
{
public:
    Layer() = delete;
    Layer(bool* value[N][N]);

    Row<N> row(const int index);
    Row<N> column(const int index);

    // operator[] returns row
    Row<N> operator[](const int index);
    Layer<N>& operator=(const bool value);

private:
    bool* _elements[N][N];
};

//

template <int N>
Layer<N>::Layer(bool* value[N][N])
: _elements{}
{
    for (const auto r : range(N))
    {
        for (const auto c : range(N))
        {
            _elements[r][c] = value[r][c];
        }
    }
}

template <int N>
Row<N> Layer<N>::row(const int index)
{
    bool* initializer[N]{};
    for (const auto i : range(N))
    {
        initializer[i] = _elements[index][i];
    }
    return Row<N>(initializer);
}

template <int N>
Row<N> Layer<N>::column(const int index)
{
    bool* initializer[N]{};
    for (const auto i : range(N))
    {
        initializer[i] = _elements[i][index];
    }
    return Row<N>(initializer);
}

template <int N>
Row<N> Layer<N>::operator[](const int index)
{
    return row(index);
}

template <int N>
Layer<N>& Layer<N>::operator=(const bool value)
{
    for (const auto r : range(N))
    {
        for (const auto c : range(N))
        {
            *(_elements[r][c]) = value;
        }
    }
}

#endif