
#ifndef STATUS_BAR_HPP
#define STATUS_BAR_HPP

#include <sstream>

#include "rogue.hpp"
#include "termbox.hpp"

class StatusBar
{
public:
    StatusBar(int y, int width, const Rogue &rogue)
        : mY{y}, mWidth{width}, mRogue{rogue}
    {
    }

    void setMessage(std::string msg) { mMessage = msg; }

    void draw() const
    {
        if (mMessage != "") {
            tb_print(mMessage.c_str(), 0, mY, TB_WHITE, TB_BLACK);
            return;
        }
        auto &bag = mRogue.bag();
        auto x = mWidth - 1;

        auto drawNum = [&](int attr, int num) {
            if (num != 0) {
                do {
                    int n = num % 10;
                    num /= 10;
                    tb_change_cell(x, mY, '0' + n, attr, TB_BLACK);
                    x--;
                } while (num != 0);
                tb_change_cell(x--, mY, ' ', TB_WHITE, TB_BLACK);
            }
        };

        drawNum(TB_WHITE | TB_BOLD, bag.crystals(Color::kBlack));
        drawNum(TB_RED, bag.crystals(Color::kRed));
        drawNum(TB_GREEN, bag.crystals(Color::kGreen));
        drawNum(TB_YELLOW, bag.crystals(Color::kYellow));
        drawNum(TB_BLUE, bag.crystals(Color::kBlue));
        drawNum(TB_MAGENTA, bag.crystals(Color::kMagenta));
        drawNum(TB_CYAN, bag.crystals(Color::kCyan));
        drawNum(TB_WHITE, bag.crystals(Color::kWhite));
    }

private:
    int mY;
    int mWidth;
    const Rogue &mRogue;
    std::string mMessage;
};

#endif
