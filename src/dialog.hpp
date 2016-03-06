
#ifndef DIALOG_HPP
#define DIALOG_HPP

#include "action.hpp"

class Dialog
{
public:
    virtual ~Dialog() {}

    virtual void process(Action action) = 0;
    virtual void draw() = 0;
    virtual bool shouldClose() = 0;
};

class CrystallineStructureDialog
{

};

#endif
