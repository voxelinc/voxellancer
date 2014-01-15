#pragma once

#include <glm/glm.hpp>


class Viewport {
public:
    Viewport();
    Viewport(int x, int y, int width, int height);

    int x() const;
    int y() const;
    int width() const;
    int height() const;

    glm::vec2 offset() const;
    glm::vec2 scale() const;

protected:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

