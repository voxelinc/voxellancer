#include "bulletenginerenderer.h"

#include <glow/Program.h>

#include <glowutils/global.h>

#include "voxeleffect/voxelmesh.h"

#include "instancedbullet.h"
#include "instancedbulletprototype.h"



BulletEngineRenderer::BulletEngineRenderer(BulletEngine& engine):
    m_initialized(false),
    m_engine(engine)
{

}

BulletEngineRenderer::~BulletEngineRenderer() = default;

void BulletEngineRenderer::bindVoxelMeshTo(glow::VertexArrayObject* vao) {
    if (!m_initialized) {
        initialize();
    }

    m_voxelMesh->bindTo(vao, 0, m_program->getAttributeLocation("v_vertex"), 1, m_program->getAttributeLocation("v_normal"));
}

void BulletEngineRenderer::add(InstancedBullet* bullet) {
    auto iter = m_prototypes.find(bullet->name());

    if (iter == m_prototypes.end()) {
        iter = m_prototypes.emplace(bullet->name(), new InstancedBulletPrototype(*this, bullet->name())).first;
    }

    iter->second->add(bullet);
}

void BulletEngineRenderer::remove(InstancedBullet* bullet) {
    auto iter = m_prototypes.find(bullet->name());
    assert(iter != m_prototypes.end());

    iter->second->remove(bullet);
}

void BulletEngineRenderer::draw(const Camera& camera) {
    if (!m_initialized) {
        initialize();
    }

    m_program->use();

    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("time", m_engine.time());

    for (auto& pair : m_prototypes) {
        pair.second->draw(camera, m_program);
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
    // TODO: Store bullets
}

void BulletEngineRenderer::afterContextRebuild() {
    // Reinsert bullets
}

