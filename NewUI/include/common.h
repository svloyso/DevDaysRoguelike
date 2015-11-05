#pragma once

inline int get_colorpair(int fg, int bg) {
    return 1 + fg*8 + bg;
}
