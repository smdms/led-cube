#ifndef ROW_H
#define ROW_H

template <int N>
class Row
{
public:
    Row() = delete;
    Row(bool* value[N]);

    // all the same, for convenience
    bool& at(const int index);
    bool& row(const int index);
    bool& column(const int index);
    bool& operator[](const int index);

    Row& operator=(const bool value);

private:
    bool* _elements[N];
};

template <int N>
Row<N>::Row(bool *value[N])
: _elements{}
{
    for (const auto i : range(N))
    {
        _elements[i] = value[i];
    }
}

template <int N>
bool& Row<N>::at(const int index)
{
    return *(_elements[index]);
}

template <int N>
bool& Row<N>::row(const int index)
{
    return at(index);
}

template <int N>
bool& Row<N>::column(const int index)
{
    return at(index);
}

template <int N>
bool& Row<N>::operator[](const int index)
{
    return at(index);
}

template <int N>
Row<N>& Row<N>::operator=(const bool value)
{
    for (const auto i : range(N))
    {
        *(_elements[i]) = value;
    }
    return *this;
}

#endif