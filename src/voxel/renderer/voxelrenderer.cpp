

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <glow/Uniform.h>
#include <glow/Program.h>
#include <glow/logging.h>
#include <glowutils/global.h>

#include "camera/camera.h"

#include "voxelrenderer.h"
#include "voxel/voxelcluster.h"

#include "voxeleffect/voxelmesh.h"
#include "voxel/voxelrenderdata.h"

#include "normalvoxelrenderer.h"
#include "instancedvoxelrenderer.h"


std::weak_ptr<VoxelRenderer> VoxelRenderer::s_instance;


VoxelRenderer::VoxelRenderer() :
    m_prepared(false),
    m_voxelMesh(new VoxelMesh()),
    m_normalRenderer(new NormalVoxelRenderer()),
    m_instancedRenderer(new InstancedVoxelRenderer())
{
    glow::debug("Create Voxelrenderer");
}

void VoxelRenderer::prepareDraw(const Camera& camera, bool withBorder) {
    m_normalRenderer->prepareDraw(camera, withBorder);
    m_instancedRenderer->prepareDraw(camera, withBorder);

    m_prepared = true;
}

void VoxelRenderer::draw(VoxelCluster& cluster) {
    if (cluster.isInstanced()) {
        m_instancedRenderer->draw(cluster);
    } else {
        m_normalRenderer->draw(cluster);
    }
}


void VoxelRenderer::afterDraw() {
    m_normalRenderer->afterDraw();
    m_instancedRenderer->afterDraw();
}

bool VoxelRenderer::prepared() {
    return m_prepared;
}

VoxelMesh& VoxelRenderer::voxelMesh() {
    assert(!s_instance.expired());
    return *s_instance.lock()->m_voxelMesh;
}

std::shared_ptr<VoxelRenderer> VoxelRenderer::instance() {
    if (std::shared_ptr<VoxelRenderer> renderer = s_instance.lock()) {
        return renderer;
    } else {
        renderer = std::shared_ptr<VoxelRenderer>(new VoxelRenderer());
        s_instance = renderer;
        return renderer;
    }
}

int VoxelRenderer::getAttributeLocation(const std::string& name) {
    int location = m_normalRenderer->program()->getAttributeLocation(name);
    assert(location == m_instancedRenderer->program()->getAttributeLocation(name));
    return location;
}

glm::vec3 VoxelRenderer::getLightDir() const {
    glm::vec3 lightDir = m_normalRenderer->program()->getUniform<glm::vec3>("lightdir")->value();
    assert(lightDir == m_instancedRenderer->program()->getUniform<glm::vec3>("lightdir")->value());
    return lightDir;
}

void VoxelRenderer::setLightDir(glm::vec3 lightDir) {
    m_normalRenderer->program()->setUniform("lightdir", lightDir);
    m_instancedRenderer->program()->setUniform("lightdir", lightDir);
}
