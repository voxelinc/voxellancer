#include "bulletenginerenderer.h"

#include <glow/Program.h>

#include <glowutils/global.h>

#include "camera/camera.h"

#include "voxeleffect/voxelmesh.h"

#include "world/world.h"

#include "instancedbullet.h"
#include "instancedbulletcontainer.h"


BulletEngineRenderer::BulletEngineRenderer():
    m_initialized(false)
{

}

BulletEngineRenderer::~BulletEngineRenderer() = default;

int BulletEngineRenderer::location(const std::string& attribute) {
    if (!m_initialized) {
        initialize();
    }
    return m_program->getAttributeLocation(attribute);
}

void BulletEngineRenderer::add(InstancedBulletContainer* container) {
    m_containers.insert(container);
}

void BulletEngineRenderer::remove(InstancedBulletContainer* container) {
    m_containers.erase(container);
}

void BulletEngineRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    m_program->use();

    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("time", World::instance()->time());

    for (InstancedBulletContainer* container : m_containers) {
        container->draw(m_program);
    }

    m_program->release();
}

void BulletEngineRenderer::initialize() {
    initializeProgram();

    m_initialized = true;
}

void BulletEngineRenderer::initializeProgram() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/bulletengine/bullet.vert"),
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/lib/quaternion.glsl"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/bulletengine/bullet.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
    );
    m_program->link();
}

void BulletEngineRenderer::beforeContextDestroy() {
    m_initialized = false;
}

void BulletEngineRenderer::afterContextRebuild() {
}

