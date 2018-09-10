#ifndef WALK_ANIMATION_H
#define WALK_ANIMATION_H

#include "config.h"
#include "output.h"

template <int N>
class WalkAnimation : public Animation<N>
{
public:
    WalkAnimation();
    ~WalkAnimation() = default;

    void play();

private:
    Cube<N> _frame;
    MatrixLedOutput<N> _output;
};

//

template <int N>
WalkAnimation<N>::WalkAnimation()
: _frame()
, _output(ADDRESS_PINS, GROUND_PINS)
{}

template <int N>
void WalkAnimation<N>::play()
{
    for (const auto l : range(N))
    {
        for (const auto r : range(N))
        {
            for (const auto c : range(N))
            {
                _frame = 0;
                _frame[l][r][c] = 1;
                _output.draw(_frame, 33);
            }
        }
    }
}

#endif