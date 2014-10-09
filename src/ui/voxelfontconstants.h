#pragma once

enum class FontSize {
    SIZE3x5,
    SIZE5x7
};

enum class FontAlign {
    LEFT,
    CENTER,
    RIGHT
};

enum class TextOrientation {
    FORWARDS, // facing straight forward, "normal text"
    SPHERE_STRAIGHT // on-helmet effect, facing in look direction from pov
};

enum class ButtonStyle {
    PLAIN,
    BORDERED,
    BORDERED_FILLED
};