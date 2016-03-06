
#ifndef OBSTRUCTION_MATRIX_HPP
#define OBSTRUCTION_MATRIX_HPP

class ObstructionMatrix
{
public:
    virtual ~ObstructionMatrix() {}

    virtual bool hasObstruction(int x, int y) const = 0;
};

#endif
