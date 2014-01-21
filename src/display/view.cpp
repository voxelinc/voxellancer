#include "view.h"

View::View(const Viewport& viewport):
    m_viewport(viewport)
{

}

View::~View() {

}

void View::setViewport(const Viewport& viewport) {
    m_viewport = viewport;
}
