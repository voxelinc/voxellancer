#pragma once
#include <memory>
#include <glm/glm.hpp>

class Camera;
class VoxelCluster;
class VoxelMesh;

class NormalVoxelRenderer;
class InstancedVoxelRenderer;

class VoxelRenderer {
public:
    void prepareDraw(const Camera& camera, bool withBorder = true);
    void draw(VoxelCluster& cluster);
    void afterDraw();

    int getAttributeLocation(const std::string& name);

    glm::vec3 getLightDir() const;
    void setLightDir(glm::vec3 lightDir);

    bool prepared();

    static std::shared_ptr<VoxelRenderer> instance();
    static VoxelMesh& voxelMesh();

protected:
    std::unique_ptr<VoxelMesh> m_voxelMesh;
    std::unique_ptr<NormalVoxelRenderer> m_normalRenderer;
    std::unique_ptr<InstancedVoxelRenderer> m_instancedRenderer;
    bool m_prepared;

    static std::weak_ptr<VoxelRenderer> s_instance;

    VoxelRenderer();
};

