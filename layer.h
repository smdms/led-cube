#ifndef LAYER_H
#define LAYER_H

#include "range.h"

template <int N>
class Layer
{
public:
    Layer();
    Layer(int value);

    int value() const;
    void set(int value);
    void write(const int (&addressPins)[N * N]) const;

private:
    const int mask() const;

    int _value;
};

// template function definitions //////////////////////////////////////////////

template <int N>
Layer<N>::Layer()
: _value(0)
{}

template <int N>
Layer<N>::Layer(int value)
: _value(value & mask())
{}

template <int N>
int Layer<N>::value() const
{
    return _value;
}

template <int N>
void Layer<N>::set(int value)
{
    _value = value & mask();
}

template <int N>
void Layer<N>::write(const int (&addressPins)[N * N]) const
{
    int value = _value;
    for (const auto pin : addressPins)
    {
        digitalWrite(pin, value & 1);
        value = value >> 1;
    }
}

template <int N>
const int Layer<N>::mask() const
{
    int ret = 0;
    for (const auto i : range(N * N))
    {
        ret = (ret << 1) + 1;
    }
    return ret;
}

#endif