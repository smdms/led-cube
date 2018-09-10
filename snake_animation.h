#ifndef SNAKE_PATH_ANIMATION
#define SNAKE_PATH_ANIMATION

template <int N>
class SnakeAnimation : public Animation<N>
{
public:
    template <int length>
    SnakeAnimation(
        const int snakeLength,
        const Coordinates (&path)[length],
        const bool repeat = false,
        const unsigned long speed = 100UL);

    ~SnakeAnimation();

    // play from start to end
    void play(const MatrixLedOutput<N>& output) override;

    // go to first frame
    void start();
    void advance(const int frames = 1) override;
    void reset() override;

    Cube<N> value() override;
    void draw(const MatrixLedOutput<N>& output) override;

    operator bool();

private:
    void targetNextPathNode();
    bool snakeHasBody();
    Coordinates nextSnakeHead(const Coordinates& target);

    Cube<N> _frame;

    // _snakeBody is used as a circular buffer
    int _snakeLength;
    int _snakeIndex;
    Coordinates* _snakeBody;

    int _pathLength;
    int _pathIndex;
    const Coordinates* const _path;
    const Coordinates* _target;

    const bool _repeat;
    const unsigned long _speed;
};

template <int N>
template <int length>
SnakeAnimation<N>::SnakeAnimation(
    const int snakeLength,
    const Coordinates (&path)[length],
    const bool repeat,
    const unsigned long speed)
: _frame()
, _snakeLength(snakeLength)
, _snakeIndex(0)
, _snakeBody(new Coordinates[_snakeLength])
, _pathLength(length)
, _pathIndex(0)
, _path(new Coordinates[_pathLength])
, _target(&(_path[0]))
, _repeat(repeat)
, _speed(speed)
{
    for (const auto i : range(_pathLength))
    {
        _path[i] = path[i];
    }

    reset();
}

template <int N>
SnakeAnimation<N>::~SnakeAnimation()
{
    delete[] _snakeBody;
    delete[] _path;
}

template <int N>
void SnakeAnimation<N>::play(const MatrixLedOutput<N>& output)
{
    start();

    do
    {
        draw(output);
        advance();
    } while (snakeHasBody());

    reset();
}

template <int N>
void SnakeAnimation<N>::start()
{
    reset();
    advance();
}

template <int N>
void SnakeAnimation<N>::advance(const int frames)
{
    for (const auto i : range(frames))
    {
        while (_target)
        {
            /*if (!snakeHasBody())
            {
                ret = _path[0];
                return ret;
            }*/

            // if there is no snake, then we draw the first frame
            const Coordinates &newHead = snakeHasBody() ? 
                                            nextSnakeHead(*_target) :
                                            _path[0];
            
            // move to next position (tail) in snake body
            _snakeIndex = ++_snakeIndex % _snakeLength;

            Coordinates &snakeHead = _snakeBody[_snakeIndex];
            
            // turn off the tail, write value of head, turn on head
            if (snakeHead.valid())
            {
                _frame.at(snakeHead) = 0;
            }
            snakeHead = newHead;
            _frame.at(snakeHead) = 1;

            // if we've reached the target, move to next target; using while
            // instead of if to skip repeated target nodes
            while (snakeHead == *_target)
            {
                targetNextPathNode();
            }

            return;
        }

        // ran out of path nodes
        _snakeIndex = ++_snakeIndex % _snakeLength;
        _frame.at(_snakeBody[_snakeIndex]) = 0;
        _snakeBody[_snakeIndex].reset();
    }
}

template <int N>
void SnakeAnimation<N>::reset()
{
    for (const auto i : range(_snakeLength))
    {
        _snakeBody[i].reset();
    }

    _pathIndex = 0;
    _snakeIndex = 0;
    _frame = 0;

    _target = &(_path[0]);
}

template <int N>
Cube<N> SnakeAnimation<N>::value()
{
    return _frame;
}

template <int N>
SnakeAnimation<N>::operator bool()
{
    return snakeHasBody();
}

template <int N>
void SnakeAnimation<N>::targetNextPathNode()
{
    // go to next position in _path
    ++_pathIndex;
    if (_pathIndex < _pathLength)
    {
        _target = &(_path[_pathIndex]);
    }
    else
    {
        // ran out of path nodes
        if (_repeat)
        {
            _pathIndex = 0;
            _target = &(_path[0]);
        }
        else
        {
            _target = 0;
        }
    }
}

template <int N>
void SnakeAnimation<N>::draw(const MatrixLedOutput<N>& output)
{
    output.draw(_frame, _speed);
}

template <int N>
bool SnakeAnimation<N>::snakeHasBody()
{
    for (const auto i : range(_snakeLength))
    {
        if (_snakeBody[i].valid())
        {
            return true;
        }
    }
    return false;
}

template <int N>
Coordinates SnakeAnimation<N>::nextSnakeHead(const Coordinates& target)
{
    Coordinates ret;
    const Coordinates &currentHead = _snakeBody[_snakeIndex];

    ret.x = currentHead.x > target.x ?
                currentHead.x - 1 :
                currentHead.x < target.x ?
                    currentHead.x + 1 :
                    currentHead.x;

    ret.y = currentHead.y > target.y ?
                currentHead.y - 1 :
                currentHead.y < target.y ?
                    currentHead.y + 1 :
                    currentHead.y;

    ret.z = currentHead.z > target.z ?
                currentHead.z - 1 :
                currentHead.z < target.z ?
                    currentHead.z + 1 :
                    currentHead.z;
    
    return ret;
}

#endif