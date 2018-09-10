#include <Arduino.h>

#include "config.h"
#include "len.h"
#include "output.h"
#include "walk_animation.h"
#include "snake_animation.h"

namespace
{

void reset()
{
    for (const auto pin : ADDRESS_PINS)
    {
        digitalWrite(pin, 0);
    }

    for (const auto pin : GROUND_PINS)
    {
        digitalWrite(pin, 1);
    }
}

} // anonymous namespace

void setup()
{
    for (const auto pin : ADDRESS_PINS)
    {
        pinMode(pin, OUTPUT);
    }

    for (const auto pin : GROUND_PINS)
    {
        pinMode(pin, OUTPUT);
    }

    reset();
    Serial.begin(19200);
}

Coordinates path[] = {
    {0, 0, 0},
    {2, 0, 0},
    {2, 2, 0},
    {2, 2, 2},
    {2, 0, 2},
    {0, 0, 2},
    {0, 2, 2},
    {0, 2, 0},
    {0, 0, 0},
};

Coordinates path2[] = {
    {2, 2, 2},
    {2, 0, 2},
    {0, 0, 2},
    {0, 2, 2},
    {0, 2, 0},
    {0, 0, 0},
    {2, 0, 0},
    {2, 2, 0},
    {2, 2, 2},
};

SnakeAnimation<SIZE> y(3, path, true, 100);
SnakeAnimation<SIZE> z(3, path2, true, 100);

const MatrixLedOutput<SIZE> output(ADDRESS_PINS, GROUND_PINS);

void loop()
{
    if (y)
    {
        y.advance();
    }
    else
    {
        y.start();
    }

    if (z)
    {
        z.advance();
    }
    else
    {
        z.start();
    }

    Cube<SIZE> frame = z.value() | y.value();
    output.draw(frame, 150);
}
