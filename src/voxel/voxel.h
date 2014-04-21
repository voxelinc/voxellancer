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
    Voxel(const glm::ivec3& gridCell, uint32_t color = 0xFFFFFFFF, float unscaledMatss = defaultUnscaledMass(), float hp = defaultHp(), float emissiveness = 0);
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

    /**
     *  Mass of the voxel if it had a scale = 1.0f. Needs to be multiplied with scale^3 to get the
     *  actual mass.
     */
    float unscaledMass() const;

    // These hooks apply only for WorldObjects and do not need to be called by pure VoxelClusters
    virtual void onRemoval();
    virtual void onDestruction();



protected:
    glm::ivec3 m_gridCell;
    VoxelTreeNode *m_voxelTreeNode;
    Visuals m_visuals;
    float m_hp;
    float m_unscaledMass;

    static Property<float>* s_defaultUnscaledMass;
    static Property<float>* s_defaultHp;

    static float defaultUnscaledMass();
    static float defaultHp();
};

