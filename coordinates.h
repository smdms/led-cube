#ifndef COORDINATES_H
#define COORDINATES_H

struct Coordinates
{
    void reset();
    bool valid() const;

    bool operator==(const Coordinates& other);
    Coordinates& operator=(const Coordinates& other);

    int x;
    int y;
    int z;
};

#endif
