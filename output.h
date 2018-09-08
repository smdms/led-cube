#ifndef OUTPUT_H
#define OUTPUT_H

#include "layer.h"

template <int N>
struct MatrixLedOutput
{
    MatrixLedOutput() = delete;
    MatrixLedOutput(
        const int (&addressPins)[N * N], 
        const int (&groundPins)[N]);
    
    void draw(const Cube<N> &cube, unsigned long duration = 250);

private:
    void reset();
    void activateLayer(int layer);
    void drawLayer(const Layer<N> &layer);

    int _addressPins[N * N];
    int _groundPins[N];
};

//

template <int N>
MatrixLedOutput<N>::MatrixLedOutput(
    const int (&addressPins)[N * N], 
    const int (&groundPins)[N])
: _addressPins{{}}
, _groundPins{}
{
    for (const auto i : range(N * N))
    {
        _addressPins[i] = addressPins[i];
        if (i < N)
        {
            _groundPins[i] = groundPins[i];
        }
    }
}

template <int N>
void MatrixLedOutput<N>::draw(const Cube<N> &cube, unsigned long duration)
{
    unsigned long start = millis();
    while (millis() < start + duration)
    {
        for (const auto layer : range(N))
        {
            reset();
            activateLayer(layer);

            int row = 0;
            int col = 0;
            for (const auto pin : _addressPins)
            {
                digitalWrite(pin, cube[layer][row][col]);
                row = ++row % N;
                col = row == 0 ? col + 1 : col;
            }
        }
    }
}

template <int N>
void MatrixLedOutput<N>::reset()
{
    for (const auto pin : _addressPins)
    {
        digitalWrite(pin, 0);
    }

    for (const auto pin : _groundPins)
    {
        digitalWrite(pin, 1);
    }
}

template <int N>
void MatrixLedOutput<N>::activateLayer(int layer)
{
    digitalWrite(_groundPins[layer], 0);
}

#endif