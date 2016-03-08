
#ifndef TERMBOX_HPP
#define TERMBOX_HPP

#include <termbox.h>

static inline int tb_print(const char *str, int x, int y, uint16_t fg,
                           uint16_t bg)
{
    const char *s = str;
    while (*s) {
        uint32_t uni;
        s += tb_utf8_char_to_unicode(&uni, s);
        tb_change_cell(x, y, uni, fg, bg);
        x++;
    }
    return s - str;
}

static inline int tb_printf(int x, int y, uint16_t fg, uint16_t bg,
                            const char *fmt, ...)
{
    char buf[4096];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(buf, sizeof(buf), fmt, vl);
    va_end(vl);
    return tb_print(buf, x, y, fg, bg);
}

#endif
