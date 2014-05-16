#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "voxel/voxeltreequery.h"
#include "voxel/voxeltree.h"
#include "voxel/voxeltreenode.h"
#include "worldobject/worldobject.h"
#include "collision/collisiondetector.h"
#include "../bandit_extension/vec3helper.h"
#include "voxel/voxel.h"


using namespace bandit;

go_bandit([](){
    describe("VoxelTree", [](){
        WorldObject* dummy;
        VoxelTree* tree;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&]() {
            dummy = new WorldObject();
            tree = &dummy->collisionDetector().voxelTree();
        });

        after_each([&]() {
            delete dummy;
        });

        it("mint is atomic and leaf", [&]() {
            AssertThat(tree->root()->isAtomic(), Equals(true));
            AssertThat(tree->root()->isLeaf(), Equals(true));
        });

        it("basic insert", [&]() {
            Voxel v(glm::ivec3(0, 0, 0));
            tree->insert(&v);

            AssertThat(tree->root()->gridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(0, 0, 0))));
        });

        it("simple insert", [&]() {
            Voxel v1(glm::ivec3(1, 1, 1));
            Voxel v2(glm::ivec3(2, 1, 1));
            Voxel v3(glm::ivec3(10, 1, 1));
            Voxel v4(glm::ivec3(2, 10, 5));

            tree->insert(&v1);
            AssertThat(tree->root()->subnodes().size(), Equals(1));
            AssertThat(tree->root()->gridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(1, 1, 1))));

            tree->insert(&v2);
            AssertThat(tree->root()->subnodes().size(), Equals(2));
            AssertThat(tree->root()->gridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(3, 3, 3))));

            tree->insert(&v3);
            AssertThat(tree->root()->subnodes().size(), Equals(2));
            AssertThat(tree->root()->gridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(15, 15, 15))));

            tree->insert(&v4);
            AssertThat(tree->root()->subnodes().size(), Equals(3));
            AssertThat(tree->root()->gridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(15, 15, 15))));
        });

        it("is moved when the transform moves", [&]() {
            Transform transform;

            AssertThat(tree->root()->sphere(transform).position(), EqualsWithDelta(glm::vec3(0), glm::vec3(0.01, 0.01, 0.01)));

            transform.move(glm::vec3(4, 3, 2));
            AssertThat(tree->root()->sphere(transform).position(), EqualsWithDelta(glm::vec3(4, 3, 2), glm::vec3(0.01, 0.01, 0.01)));

            transform.move(glm::vec3(1, 2, 3));
            transform.move(glm::vec3(-1, 2, 2));
            AssertThat(tree->root()->sphere(transform).position(), EqualsWithDelta(glm::vec3(4, 7, 7), glm::vec3(0.01, 0.01, 0.01)));
        });

        it("supports basic rotation with voxel in center", [&]() {
            Voxel v1(glm::ivec3(1, 1, 1));
            Voxel v2(glm::ivec3(0, 0, 0));
            Transform transform;

            tree->insert(&v1);

            VoxelTreeNode *n = tree->root()->subnodes().front();

            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));
            tree->insert(&v2); // Center in middle now
            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));

            transform.rotate(glm::angleAxis(glm::radians(90.0f), glm::vec3(1, 0, 0)));
            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1, -1, 1), glm::vec3(0.01, 0.01, 0.01)));
        });

        it("supports basic rotation with voxel out of center", [&]() {
            glm::vec3 v;
            Voxel v1(glm::ivec3(1, 1, 1));
            Voxel v2(glm::ivec3(0, 0, 0));
            Transform transform;

            tree->insert(&v1);

            VoxelTreeNode *n = tree->root()->subnodes().front();

            tree->insert(&v2);
            transform.setCenter(glm::vec3(0.5, 0.5, 0.5));
            transform.setPosition(glm::vec3(0.5, 0.5, 0.5));

            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1,1,1), glm::vec3(0.01, 0.01, 0.01)));
            AssertThat(tree->root()->sphere(transform).position(), EqualsWithDelta(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.01, 0.01, 0.01)));

            transform.rotate(glm::angleAxis(glm::radians(90.0f), glm::vec3(1, 0, 0)));
            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1, 0, 1), glm::vec3(0.01, 0.01, 0.01)));

            transform.rotate(glm::angleAxis(glm::radians(90.0f), glm::vec3(0, 1, 0)));
            AssertThat(n->sphere(transform).position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));
        });

        it("can be queried for voxels in sphere", [&]() {
            Sphere sphere;
            Voxel v1(glm::ivec3(1, 1, 0));
            Voxel v2(glm::ivec3(2, 2, 0));

            tree->insert(&v1);

            sphere = Sphere(glm::vec3(0,0,0), 0.5f);
            AssertThat(VoxelTreeQuery(tree, &sphere).intersectingVoxels().size(), Equals(0));

            sphere = Sphere(glm::vec3(0,0,0), 1.0f);
            AssertThat(VoxelTreeQuery(tree, &sphere).intersectingVoxels().size(), Equals(1));

            tree->insert(&v2);

            sphere = Sphere(glm::vec3(1.5,1.5,0), 0.5f);
            AssertThat(VoxelTreeQuery(tree, &sphere).intersectingVoxels().size(), Equals(2));
        });
    });
});

