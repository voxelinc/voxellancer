#include "viewport.h"

#include <GLFW/glfw3.h>


Viewport::Viewport(int x, int y, int width, int height):
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height)
{
}

int Viewport::x() const {
    return m_x;
}

int Viewport::y() const {
    return m_y;
}

int Viewport::width() const {
    return m_width;
}

int Viewport::height() const {
    return m_height;
}

glm::vec2 Viewport::offset() const {
    int width;
    int height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    return glm::vec2(
        static_cast<float>(m_x) / static_cast<float>(width),
        static_cast<float>(m_y) / static_cast<float>(height)
    );
}

glm::vec2 Viewport::scale() const {
    int width;
    int height;
    glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

    return glm::vec2(
        static_cast<float>(m_width) / static_cast<float>(width),
        static_cast<float>(m_width) / static_cast<float>(height)
    );
}

