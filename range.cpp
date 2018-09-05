#include "range.h"

// iterator ///////////////////////////////////////////////////////////////////

range::iterator::iterator(int i)
: _value(i)
{}

int range::iterator::operator*() const
{
    return _value;
}

bool range::iterator::operator!=(const iterator& rhs) const
{
    return _value != rhs._value;
}

range::iterator& range::iterator::operator++()
{
    ++_value;
}

// range //////////////////////////////////////////////////////////////////////

range::range(int stop)
: _start(0)
, _size(stop)
{}

range::range(int start, int stop)
: _start(start)
, _size(stop - start)
{}

range::iterator range::begin()
{
    return iterator(_start);
}

range::iterator range::end()
{
    return iterator(_start + _size);
}

range::const_iterator range::cbegin()
{
    return const_iterator(_start);
}

range::const_iterator range::cend()
{
    return const_iterator(_start + _size);
}
