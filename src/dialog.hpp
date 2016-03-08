
#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "action.hpp"
#include "termbox.hpp"

class Dialog
{
public:
    typedef std::function<void(std::string)> Callback;
    Dialog(int x, int y, int maxWidth, int maxHeight, const std::string &headline, const std::vector<std::string> &options, const Callback &cb) :
        mX{x}, mY{y}, mMaxWidth{maxWidth}, mMaxHeight{maxHeight}, mHeadline{headline}, mOptions{options}, mCallback{cb}
    {
        mWidth = std::max_element(std::begin(mOptions), std::end(mOptions),
            [](auto &a, auto &b) { return a.size() < b.size();
        })->size();
        mWidth = std::max(mWidth, static_cast<int>(mHeadline.size()));
        // +1 for headline.
        mHeight = 1 + mOptions.size();

        // Offset for max area.
        int xOffset = (mX + mWidth) - mMaxWidth;
        if (xOffset > 0) {
            mX -= xOffset;
        }
        int yOffset = (mY + mHeight) - mMaxHeight;
        if (yOffset > 0) {
            mY -= yOffset;
        }

        // Resize all strings for easy printing.
        for (auto &option : mOptions) {
            option.resize(mWidth, ' ');
        }
    }

    void process(Action action)
    {
        switch (action) {
        case Action::kBack:
            mShouldClose = true;
            break;
        case Action::kMoveNorth:
            mSelected = std::max(mSelected - 1, 0);
            break;
        case Action::kMoveSouth:
            mSelected = std::min(mSelected + 1, static_cast<int>(mOptions.size()) - 1);
            break;
        case Action::kMoveWest:
            mShouldClose = true;
            break;
        case Action::kMoveEast: case Action::kConfirm:
            mShouldClose = true;
            if (mSelected >= 0) {
                mCallback(mOptions[mSelected]);
            }
            break;
        default:
            break;
        }
    }

    void draw()
    {
        int y = mY;
        tb_printf(mX, y++, TB_WHITE, TB_BLUE, mHeadline.c_str());
        for (int i = 0; i < static_cast<int>(mOptions.size()); ++i) {
            int fg = TB_WHITE;
            int bg = TB_BLUE;
            if (i == mSelected) {
                std::swap(fg, bg);
            }
            tb_printf(mX, y++, fg, bg, mOptions[i].c_str());
        }
    }

    bool shouldClose() const { return mShouldClose; }

private:
    bool mShouldClose = false;
    int mSelected = -1;
    // Guidelines.
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    int mMaxWidth;
    int mMaxHeight;
    std::string mHeadline;
    std::vector<std::string> mOptions;
    Callback mCallback;
};

#endif
