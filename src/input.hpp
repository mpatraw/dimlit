
#ifndef INPUT_HPP
#define INPUT_HPP

#include <map>

#include "action.hpp"

class Input
{
public:
    Input();

    Action check(int timeout = 0);

private:
    std::map<int, Action> mKeyBindings;
};

#endif
