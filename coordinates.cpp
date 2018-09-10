#include "coordinates.h"

void Coordinates::reset()
{
    x = y = z = -1;
}

bool Coordinates::valid() const
{
    return (x != -1) && (y != -1) && (z != -1);
}

bool Coordinates::operator==(const Coordinates& other)
{
    return (x == other.x) && (y == other.y) && (z == other.z);
}

Coordinates& Coordinates::operator=(const Coordinates& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}
