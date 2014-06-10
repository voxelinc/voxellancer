#pragma once

#include <glm/glm.hpp>

#include "property/property.h"

#include "display/rendering/visuals.h"


class VoxelCluster;
class VoxelTreeNode;
class WorldObject;
class Sphere;

class Voxel {
public:
    Voxel(const glm::ivec3& gridCell, uint32_t color = 0xFFFFFF, float density = defaultDensity(), float hp = defaultHp(), float emissiveness = 0);
    Voxel(const Voxel& other);
    virtual ~Voxel();

    const glm::ivec3 &gridCell() const;

    glm::vec3 position() const;

    VoxelTreeNode *voxelTreeNode();
    void setVoxelTreeNode(VoxelTreeNode* voxelTreeNode);

    virtual void addToCluster(VoxelCluster *cluster);
    virtual void addToObject(WorldObject *object);

    virtual Visuals visuals() const;

    float hp() const;
    void applyDamage(float deltaHp);

    virtual float damageForwardingDestructionDamage();

    float density() const;

    // These hooks apply only for WorldObjects and do not need to be called by pure VoxelClusters
    virtual void onRemoval();
    virtual void onDestruction();



protected:
    glm::ivec3 m_gridCell;
    VoxelTreeNode* m_voxelTreeNode;
    Visuals m_visuals;
    float m_hp;
    float m_density;

    static Property<float>* s_defaultDensity;
    static Property<float>* s_defaultHp;

    static float defaultDensity();
    static float defaultHp();
};

