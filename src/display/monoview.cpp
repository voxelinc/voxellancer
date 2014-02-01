#include "monoview.h"


#include <GL/glew.h>
#include <GL/gl.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "geometry/viewport.h"

#include "etc/windowmanager.h"

#include "display/scene.h"


MonoView::MonoView(const Viewport& viewport):
    View(viewport),
    m_camera(m_viewport.width(), m_viewport.height())
{

}

void MonoView::setViewport(const Viewport& viewport) {
    View::setViewport(viewport);
    m_camera.setViewport(glm::ivec2(m_viewport.width(), m_viewport.height()));
}

float MonoView::fovy() const {
    return m_camera.fovy();
}

float MonoView::zNear() const {
    return m_camera.zNear();
}

float MonoView::aspectRatio() const {
    return m_camera.aspectRatio();
}

void MonoView::draw(Scene* scene, CameraHead* cameraHead) {
    glViewport(m_viewport.x(), m_viewport.y(), m_viewport.width(), m_viewport.height());

    m_camera.setPosition(cameraHead->position());
    m_camera.setOrientation(cameraHead->orientation());

    scene->draw(&m_camera);
}

