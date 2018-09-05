#ifndef RANGE_H
#define RANGE_H

struct range
{
    struct iterator
    {
        explicit iterator(int i);

        int operator*() const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator++();

    private:
        int _value;
    };

    using const_iterator = iterator;

    explicit range(int stop);
    explicit range(int start, int stop);
    //explicit range(int start, int stop, int step);

    iterator begin();
    iterator end();

    const_iterator cbegin();
    const_iterator cend();

private:
    const int _start;
    const int _size;
};

#endif