#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>


#include "utils/tostring.h"
#include "world/world.h"
#include "voxel/voxeltreequery.h"
#include "voxel/voxeltreenode.h"
#include "worldobject/worldobject.h"
#include "../bandit_extension/vec3helper.h"

using namespace bandit;



go_bandit([](){
    describe("VoxelTree", [](){
        World *world;
        WorldObject *obj;
        VoxelTreeNode *vt;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&]() {
            world = new World();
            obj = new WorldObject(1);
            vt = &obj->collisionDetector().voxeltree();
        });

        after_each([&]() {
            delete world;
            delete obj;
        });

        it("mint is atomic and leaf", [&]() {
            AssertThat(vt->isAtomic(), Equals(true));
            AssertThat(vt->isLeaf(), Equals(true));
        });

        it("basic insert", [&]() {
            obj->addVoxel(new Voxel(glm::ivec3(0, 0, 0)));
            AssertThat(vt->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(0, 0, 0))));
        });

        it("simple insert", [&]() {
            Voxel *v = new Voxel(glm::ivec3(1, 1, 1));

            obj->addVoxel(new Voxel(glm::ivec3(1, 1, 1)));
            AssertThat(vt->subnodes().size(), Equals(8));
            AssertThat(vt->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(1, 1, 1))));

            obj->addVoxel(new Voxel(glm::ivec3(5, 1, 1)));
            AssertThat(vt->subnodes().size(), Equals(8));
            AssertThat(vt->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));

            obj->addVoxel(new Voxel(glm::ivec3(2, 5, 5)));
            AssertThat(vt->subnodes().size(), Equals(8));
            AssertThat(vt->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));
        });

        it("is moved when the cluster moves", [&]() {
            AssertThat(vt->boundingSphere().position(), EqualsWithDelta(glm::vec3(0), glm::vec3(0.01, 0.01, 0.01)));

            obj->move(glm::vec3(4, 3, 2));
            AssertThat(vt->boundingSphere().position(), EqualsWithDelta(glm::vec3(4, 3, 2), glm::vec3(0.01, 0.01, 0.01)));

            obj->move(glm::vec3(1, 2, 3));
            obj->move(glm::vec3(-1, 2, 2));
            AssertThat(vt->boundingSphere().position(), EqualsWithDelta(glm::vec3(4, 7, 7), glm::vec3(0.01, 0.01, 0.01)));
        });

        // these two tests were the only ones to use the constructor with center, not sure whether to keep them
        /*it_skip("can adjust its center", [&]() {
            WorldObject *d = new WorldObject(1.0f);

            AssertThat(d->collisionDetector().voxeltree().boundingSphere().position(), EqualsWithDelta(glm::vec3(-1, -1, -1), glm::vec3(0.01, 0.01, 0.01)));
        });

        it_skip("can adjust its center and scale", [&]() {
            WorldObject *d = new WorldObject(3.0f);

            AssertThat(d->collisionDetector().voxeltree().boundingSphere().radius(), EqualsWithDelta(2.5f, 0.1f));
            AssertThat(d->collisionDetector().voxeltree().boundingSphere().position(), EqualsWithDelta(glm::vec3(-3, -3, -3), glm::vec3(0.01, 0.01, 0.01)));
        });*/

        // skip until is is clear what this test is supposed to test :)
        it_skip("initially positions all subnodes right", [&]() {
            WorldObject *d = new WorldObject(6);

            d->addVoxel(new Voxel(glm::ivec3(1, 1, 1))); // There are 8 subnodes now

            for(VoxelTreeNode *subnode : d->collisionDetector().voxeltree().subnodes()) {
                float distance = glm::length(subnode->boundingSphere().position());
                AssertThat(distance, EqualsWithDelta(5.2, 0.01)); // what is supposed to happen here?
            }
        });

        it_skip("supports basic rotation with voxel in center", [&]() {
            glm::vec3 v;
            VoxelTreeNode *n = nullptr;

            obj->addVoxel(new Voxel(glm::ivec3(1, 1, 1)));

            for (VoxelTreeNode *subnode : obj->collisionDetector().voxeltree().subnodes()) {
                if (subnode->voxel() != nullptr) {
                    n = subnode;
                }
            }
            assert(n != nullptr);

            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));
            obj->addVoxel(new Voxel(glm::ivec3(0, 0, 0))); // Center in middle now
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));

            obj->rotate(glm::angleAxis((float)90.0, glm::vec3(1, 0, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 0, 1), glm::vec3(0.01, 0.01, 0.01)));

        });

        // see above
        it_skip("supports basic rotation with voxel out of center", [&]() {
            glm::vec3 v;
            VoxelTreeNode *n = nullptr;

            obj->addVoxel(new Voxel(glm::ivec3(1, 1, 1)));
            //obj->transform().setCenter(glm::vec3(1,1,0));

            for(VoxelTreeNode *subnode : obj->collisionDetector().voxeltree().subnodes()) {
                if(subnode->voxel() != nullptr) {
                    n = subnode;
                }
            }

            obj->addVoxel(new Voxel(glm::ivec3(0, 0, 0)));
            assert(n != nullptr);

            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1,1,1), glm::vec3(0.01, 0.01, 0.01)));
            AssertThat(vt->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.01, 0.01, 0.01)));

            obj->rotate(glm::angleAxis((float)90.0, glm::vec3(1, 0, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 0, 1), glm::vec3(0.01, 0.01, 0.01)));

            obj->rotate(glm::angleAxis((float)90.0f, glm::vec3(0, 1, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 1, 1), glm::vec3(0.01, 0.01, 0.01)));
        });

        // assumes the voxel is at 1,1,0 - but because of the center-adjust the voxel is in origin
        it_skip("can be queried for voxels in sphere", [&]() {
            Sphere sphere;

            obj->addVoxel(new Voxel(glm::ivec3(1, 1, 0)));

            sphere = Sphere(glm::vec3(0,0,0), 0.5f);
            AssertThat(VoxelTreeQuery(vt, &sphere).intersectingVoxels().size(), Equals(0));

            sphere =  Sphere(glm::vec3(0,0,0), 1.0f);
            AssertThat(VoxelTreeQuery(vt, &sphere).intersectingVoxels().size(), Equals(1));

            obj->addVoxel(new Voxel(glm::ivec3(2, 2, 0)));

            sphere = Sphere(glm::vec3(1.5,1.5,0), 0.5f);
            AssertThat(VoxelTreeQuery(vt, &sphere).intersectingVoxels().size(), Equals(2));
        });
    });
});

