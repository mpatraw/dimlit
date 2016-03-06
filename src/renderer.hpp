
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "color.hpp"

enum class Attributes
{
    kNone,
    kBold,
    kUnderline,
    kReverse
};

class Renderer
{
public:
    virtual ~Renderer() {}

    virtual void drawGlyph();
};

#endif
