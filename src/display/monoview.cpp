#include "monoview.h"


#include <GL/glew.h>
#include <GL/gl.h>

#include <glow/FrameBufferObject.h>

#include "camera/camera.h"
#include "camera/camerahead.h"

#include "display/scene.h"

#include "geometry/viewport.h"

#include "rendering/antialiasing.h"


MonoView::MonoView(const Viewport& viewport):
    View(viewport),
    m_camera(new Camera(m_viewport.width(), m_viewport.height())),
    m_antialiasing("vfx.antialiasing")
{

}

void MonoView::setViewport(const Viewport& viewport) {
    View::setViewport(viewport);
    m_camera->setViewport(glm::ivec2(m_viewport.width(), m_viewport.height()));
}

float MonoView::fovy() const {
    return m_camera->fovy();
}

float MonoView::zNear() const {
    return m_camera->zNear();
}

float MonoView::aspectRatio() const {
    return m_camera->aspectRatio();
}

void MonoView::draw(const Scene& scene, const CameraHead& cameraHead) {
    int samplingFactor = 1;
    if (m_antialiasing.get() == Antialiasing::SSAA) {
        samplingFactor = 2;
    }
    int sampleWidth = static_cast<int>(m_viewport.width() * samplingFactor);
    int sampleHeight = static_cast<int>(m_viewport.height() * samplingFactor);

    glViewport(m_viewport.x(), m_viewport.y(), sampleWidth, sampleHeight);

    m_camera->setViewport(glm::ivec2(sampleWidth, sampleHeight));
    m_camera->setPosition(cameraHead.position());
    m_camera->setOrientation(cameraHead.orientation());

    scene.draw(*m_camera, glow::FrameBufferObject::defaultFBO(), m_viewport);
}

