#include "monoview.h"


#include <GL/glew.h>
#include <GL/gl.h>

#include <glow/FrameBufferObject.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "geometry/viewport.h"

#include "etc/windowmanager.h"

#include "display/scene.h"


MonoView::MonoView(const Viewport& viewport):
    View(viewport)
{

}

void MonoView::draw(Scene* scene, CameraHead* cameraHead) {
    glViewport(m_viewport.x(), m_viewport.y(), m_viewport.width(), m_viewport.height());

    Camera camera(m_viewport.width(), m_viewport.height());

    camera.setPosition(cameraHead->position());
    camera.setOrientation(cameraHead->orientation());

    scene->draw(&camera, glow::FrameBufferObject::defaultFBO(), glm::ivec2(m_viewport.width(), m_viewport.height()));
}

