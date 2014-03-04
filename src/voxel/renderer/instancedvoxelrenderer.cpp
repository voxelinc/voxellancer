#include "instancedvoxelrenderer.h"


#include <glow/Array.h>
#include <glow/Shader.h>
#include <glow/Texture.h>
#include <glow/VertexArrayObject.h>
#include <glow/VertexAttributeBinding.h>
#include <glow/Program.h>
#include <glow/Buffer.h>
#include <glow/Shader.h>
#include <glowutils/global.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "camera/camera.h"

#include "voxel/voxelcluster.h"

#include "voxeleffect/voxelmesh.h"
#include "voxel/voxelrenderdata.h"



InstancedVoxelRenderer::InstancedVoxelRenderer() :
    m_program(0),
    m_clusterData(),
    m_clustersMap()
{
    glow::debug("Create Voxelrenderer");
    createAndSetupShaders();
}

void InstancedVoxelRenderer::prepareDraw(const Camera& camera, bool withBorder) {
    glEnable(GL_DEPTH_TEST);

    m_program->setUniform("projection", camera.projection());
    m_program->setUniform("view", camera.view());
    m_program->setUniform("viewProjection", camera.viewProjection());
    m_program->setUniform("withBorder", (withBorder ? 1.0f : 0.0f));

    glProvokingVertex(GL_LAST_VERTEX_CONVENTION);
}

void InstancedVoxelRenderer::draw(VoxelCluster& cluster) {
    assert(cluster.isInstanced());
    std::vector<VoxelCluster*>& clusters = m_clustersMap[&cluster.voxelRenderData()];
    if (clusters.size() == 0) {
        //setup(clustser.voxelRenderData())
    }
    clusters.push_back(&cluster);
}


void InstancedVoxelRenderer::afterDraw() {
    m_program->use();

    for (auto& pair : m_clustersMap)
    {
        drawInstances(pair.first, pair.second);
        pair.second.clear();
    }

    m_program->release();
}

void InstancedVoxelRenderer::createAndSetupShaders() {
    m_program = new glow::Program();
    m_program->attach(
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/voxelcluster/instancedvoxelcluster.vert"),
        glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/shader/lib/quaternion.glsl"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/voxelcluster/voxelcluster.frag"),
        glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/shader/lib/voxel.frag")
        );

    m_clusterBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
}

void InstancedVoxelRenderer::beforeContextDestroy() {
    m_program = nullptr;
    m_clusterBuffer = nullptr;
    m_clustersMap.clear();
}

void InstancedVoxelRenderer::afterContextRebuild() {
    createAndSetupShaders();
}

int InstancedVoxelRenderer::getAttributeLocation(const std::string& name) {
    return m_program->getAttributeLocation(name);
}

glow::Program* InstancedVoxelRenderer::program() {
    return m_program;
}

void InstancedVoxelRenderer::drawInstances(IVoxelRenderData* renderData, std::vector<VoxelCluster*> clusters) {
    m_clusterData.clear();

    for (VoxelCluster* cluster : clusters)
    {
        const Transform& transform = cluster->transform();
        m_clusterData.push_back(ClusterData{ transform.position(), transform.orientation(), 
                                             transform.scale(), transform.center() });
    }
    m_clusterBuffer->setData(m_clusterData, GL_STREAM_DRAW);

    renderData->vertexArrayObject()->bind();
    glVertexAttribDivisor(m_program->getAttributeLocation("v_vertex"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_normal"), 0);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_position"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_color"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("v_emissiveness"), 1);
    glVertexAttribDivisor(m_program->getAttributeLocation("m_position"), renderData->voxelCount());
    glVertexAttribDivisor(m_program->getAttributeLocation("m_orientation"), renderData->voxelCount());
    glVertexAttribDivisor(m_program->getAttributeLocation("m_scale"), renderData->voxelCount());
    glVertexAttribDivisor(m_program->getAttributeLocation("m_center"), renderData->voxelCount());
    renderData->vertexArrayObject()->drawArraysInstanced(GL_TRIANGLE_STRIP, 0, 14, renderData->voxelCount() * m_clusterData.size());

}
