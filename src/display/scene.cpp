#include "scene.h"

#include <glow/logging.h>

#include "camera/camera.h"

#include "geometry/viewport.h"

#include "display/rendering/framebuffer.h"
#include "display/rendering/renderpipeline.h"
#include "display/rendering/blitter.h"
#include "display/rendering/buffernames.h"


Scene::Scene():
    m_outputBlitter(new Blitter()),
    m_renderPipeline(RenderPipeline::getDefault()),
    m_framebuffer(nullptr),
    m_currentOutputBuffer(0)
{

}

Scene::~Scene() = default;

void Scene::draw(const Camera& camera, glow::FrameBufferObject* destination, const Viewport& destinationViewport, EyeSide side) const {
    if (m_framebuffer == nullptr) {
        m_framebuffer.reset(new FrameBuffer(m_renderPipeline->bufferCount()));
    }

    m_framebuffer->setResolution(camera.viewport());
    m_framebuffer->clear();
    m_framebuffer->setDrawBuffers({ BufferNames::Color, BufferNames::NormalZ, BufferNames::Emissisiveness });

    drawImpl(camera);

    RenderMetaData metadata(camera, side);
    m_renderPipeline->apply(*m_framebuffer, metadata);

    // set viewport to original resolution
    glViewport(destinationViewport.x(), destinationViewport.y(), destinationViewport.width(), destinationViewport.height());

    // transfer rendered image to target framebuffer
    m_outputBlitter->setInputMapping({ { "source", m_currentOutputBuffer } });
    m_outputBlitter->apply(*m_framebuffer, destination);
}

void Scene::setOutputBuffer(int i) {
    m_currentOutputBuffer = glm::min(i, m_renderPipeline->bufferCount() - 1);
    glow::info("Switched to output-buffer: %;", bufferNames[m_currentOutputBuffer]);
}

void Scene::addRenderPass(const std::shared_ptr<RenderPass>& renderPass, int pos) {
    m_renderPipeline->add(renderPass, pos);
}
