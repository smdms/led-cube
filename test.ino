#include <Arduino.h>

#include "len.h"
#include "output.h"

void operator delete(void* ptr, unsigned int size)
{
    delete ptr;
}

namespace
{

const int SIZE = 3;
const int ADDRESS_PINS[SIZE * SIZE] = {2, 4, 7, 8, 9, 10, 11, 12, 13};
const int GROUND_PINS[SIZE] = {3, 5, 6};

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
    Serial.begin(9600);
}

using Cube3 = Cube<SIZE>;

void loop()
{
    Cube<3> cube;
    MatrixLedOutput<3> output(ADDRESS_PINS, GROUND_PINS);

    for (const auto l : range(3))
    {
        for (const auto r : range(3))
        {
            for (const auto c : range(3))
            {
                cube = 0;
                cube[l][r][c] = 1;
                output.draw(cube);
            }
        }
    }
}
