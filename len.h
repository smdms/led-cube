#ifndef LEN_H
#define LEN_H

template <typename T, int N>
int len(T (&arr)[N])
{
    return N;
}

#endif