#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glow/ref_ptr.h>
#include <glow/Array.h>

#include "etc/contextdependant.h"



namespace glow {
    class Texture;
    class Program;
    class VertexArrayObject;
    class Buffer;
    template<typename T>
    class Uniform;
};

class Camera;
class VoxelCluster;
class VoxelMesh;
class IVoxelRenderData;

class InstancedVoxelRenderer : public ContextDependant {
public:
    InstancedVoxelRenderer();

    void prepareDraw(const Camera& camera, bool withBorder = true);
    void draw(VoxelCluster& cluster);
    void afterDraw();

    int getAttributeLocation(const std::string& name);
    glow::Program* program();

protected:
    struct ClusterData {
        glm::vec3 position;
        glm::quat orientation;
        float scale;
        glm::vec3 center;
    };
    
    glow::ref_ptr<glow::Program> m_program;

    glow::Uniform<glm::mat4>* m_modelMatrixUniform;
    glow::Uniform<float>* m_emissivenessUniform;

    glow::ref_ptr<glow::Buffer> m_clusterBuffer;
    glow::Array<ClusterData> m_clusterData;
    std::unordered_map<IVoxelRenderData*, std::vector<VoxelCluster*>> m_clustersMap;

    void createAndSetupShaders();
    virtual void beforeContextDestroy() override;
    virtual void afterContextRebuild() override;

    void drawInstances(IVoxelRenderData* renderData, std::vector<VoxelCluster*> clusters);

};

