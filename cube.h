#ifndef CUBE_H
#define CUBE_H

#include "range.h"
#include "layer.h"

template <int N>
class Cube
{
public:
    Cube();
    Cube(const int (&layerValues)[N]);
    Cube(const bool (&rawValues)[N][N][N]);
    ~Cube();

    void write(const int (&addressPins)[N * N], const int (&groundPins)[N]) const;

    Layer<N>& operator[](int index);

private:
    const int layerMask(int layer);

    bool _elements[N][N][N];

    Layer<N>* _layers;
};

// template function definitions //////////////////////////////////////////////

template <int N>
Cube<N>::Cube()
: _elements()
, _layers(new Layer<N>[N]())
{}

template <int N>
Cube<N>::Cube(const bool (&rawValues)[N][N][N])
: _elements{rawValues}
{}

/*
 * constructing a 3x3 example cube from initializer list:
 *
 *          bottom
 *      middle |
 *    top  |   |
 *     |   |   |
 *    --- --- ---
 * {0b000'000'000,<--------------------
 *  0b000'000'000,                    |
 *  0b000'000'000}                    |
 *              ^                     |
 *              |                     |
 * led closest to pin #0 on the pcb   |
 * led closest to pin #13 -------------
 */
template <int N>
Cube<N>::Cube(const int (&layerValues)[N])
: _elements()
, _layers(new Layer<N>[N]())
{
    for (const auto layer : range(N))
    {
        int layerValue = 0;
        auto mask = layerMask(layer);

        // apply the mask and shift to extract the value for this layer from each input layer value
        for (const auto i : layerValues)
        {
            int val = (i & mask) >> (N * layer);
            layerValue = (layerValue << N) + val;
        }

        _layers[layer].set(layerValue);
    }
}

/*
 * constructing a 3x3 example cube from initializer list:
 * 
 * {0b000'000'000,<--top
 *  0b000'000'000,<--middle
 *  0b000'000'000}<--bottom
 * 
template <int N>
Cube<N>::Cube(const int (&layerValues)[N])
: _layers(new Layer<N>[N]())
{
    for (const auto l : range(N))
    {
        _layers[l].set(layerValues[l]);
    }
}
*/

template <int N>
Cube<N>::~Cube()
{
    delete[] _layers;
}

template <int N>
void Cube<N>::write(const int (&addressPins)[N * N], const int (&groundPins)[N]) const
{
    // iterate over layers
    for (const auto layer : range(N))
    {
        reset();

        // activate layer
        digitalWrite(groundPins[layer], 0);

        // write LEDs
        _layers[layer].write(addressPins);
    }
}

template <int N>
Layer<N>& Cube<N>::operator[](int index)
{
    return _layers[index];
}

template <int N>
const int Cube<N>::layerMask(int layer)
{
    int layerMask = 0;
    for (const auto i : range(N))
    {
        layerMask = (layerMask << 1) + 1;
    }

    layerMask = layerMask << (N * layer);

    return layerMask;
}

#endif