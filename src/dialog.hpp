
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
    virtual ~Dialog() = default;

    virtual void process(Action action) = 0;
    virtual void draw() = 0;
    bool shouldClose() const { return mShouldClose; }

protected:
    void close() { mShouldClose = true; }

private:
    bool mShouldClose = false;
};

template <typename T> class BasicDialog : public Dialog
{
public:
    typedef std::pair<std::string, T> Option;
    typedef std::function<void(std::string, const T &t)> Callback;
    BasicDialog(int x, int y, int maxWidth, int maxHeight,
                const std::string &headline, const std::vector<Option> &options,
                const Callback &cb)
        : mX{x}, mY{y}, mMaxWidth{maxWidth}, mMaxHeight{maxHeight},
          mHeadline{headline}, mOptions{options}, mCallback{cb}
    {
        mWidth = std::max_element(std::begin(mOptions), std::end(mOptions),
                                  [](auto &a, auto &b) {
                                      return a.first.size() < b.first.size();
                                  })
                     ->first.size();
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
            option.first.resize(mWidth, ' ');
        }
    }

    void process(Action action) override
    {
        switch (action) {
        case Action::kBack:
            close();
            break;
        case Action::kMoveNorth:
            mSelected = std::max(mSelected - 1, 0);
            break;
        case Action::kMoveSouth:
            mSelected =
                std::min(mSelected + 1, static_cast<int>(mOptions.size()) - 1);
            break;
        case Action::kMoveWest:
            close();
            break;
        case Action::kMoveEast:
        case Action::kConfirm:
            close();
            if (mSelected >= 0) {
                mCallback(mOptions[mSelected].first,
                          mOptions[mSelected].second);
            }
            break;
        default:
            break;
        }
    }

    void draw() override
    {
        int y = mY;
        tb_printf(mX, y++, TB_WHITE, TB_BLUE, mHeadline.c_str());
        for (int i = 0; i < static_cast<int>(mOptions.size()); ++i) {
            int fg = TB_WHITE;
            int bg = TB_BLUE;
            if (i == mSelected) {
                std::swap(fg, bg);
            }
            tb_printf(mX, y++, fg, bg, mOptions[i].first.c_str());
        }
    }

private:
    int mSelected = -1;
    // Guidelines.
    int mX;
    int mY;
    int mWidth;
    int mHeight;
    int mMaxWidth;
    int mMaxHeight;
    std::string mHeadline;
    std::vector<Option> mOptions;
    Callback mCallback;
};

#endif
