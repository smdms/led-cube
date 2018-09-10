#ifndef ANIMATION_H
#define ANIMATION_H

#include "range.h"
#include "cube.h"
#include "output.h"

template <int N>
class Animation
{
public:
    virtual ~Animation() = default;

    virtual void play(const MatrixLedOutput<N>& output) = 0;
    virtual void advance(const int frames) = 0;
    virtual void reset() = 0;

    virtual Cube<N> value() = 0;
    virtual void draw(const MatrixLedOutput<N>& output) = 0;
};

#endif