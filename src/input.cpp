
#include <termbox.h>

#include "input.hpp"

Input::Input()
{
    mKeyBindings[TB_KEY_ARROW_UP] = Action::kMoveNorth;
    mKeyBindings[TB_KEY_ARROW_DOWN] = Action::kMoveSouth;
    mKeyBindings[TB_KEY_ARROW_LEFT] = Action::kMoveWest;
    mKeyBindings[TB_KEY_ARROW_RIGHT] = Action::kMoveEast;
    mKeyBindings[TB_KEY_ESC] = Action::kBack;
    mKeyBindings[TB_KEY_ENTER] = Action::kConfirm;
    mKeyBindings[TB_KEY_SPACE] = Action::kConfirm;
    mKeyBindings['k'] = Action::kMoveNorth;
    mKeyBindings['j'] = Action::kMoveSouth;
    mKeyBindings['h'] = Action::kMoveWest;
    mKeyBindings['l'] = Action::kMoveEast;
    mKeyBindings['c'] = Action::kConfirm;
    mKeyBindings['Q'] = Action::kQuit;
}

Action Input::check(int timeout)
{
    tb_event ev;
    int type = tb_peek_event(&ev, timeout);
    switch (type) {
    case TB_EVENT_KEY: {
        auto key = ev.key != 0 ? ev.key : ev.ch;
        auto iter = mKeyBindings.find(key);
        if (iter == mKeyBindings.end()) {
            return Action::kNone;
        }
        return iter->second;
    }
    default:
        return Action::kNone;
    }
}
