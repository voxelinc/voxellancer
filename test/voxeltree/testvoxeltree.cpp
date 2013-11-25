#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "voxel/voxeltreenode.h"
#include "worldtree/worldtreecluster.h"

#include "utils/tostring.h"
#include "../bandit_extension/vec3helper.h"

using namespace bandit;



go_bandit([](){
    describe("Voxeltree", [](){
        WorldTreeCluster *c;
        VoxeltreeNode *r;

        before_each([&]() {
            c = new WorldTreeCluster();
            r = &c->voxeltree();
        });

        after_each([&]() {
            delete c;
        });

        it("mint is atomic and leaf", [&]() {
            AssertThat(r->isAtomic(), Equals(true));
            AssertThat(r->isLeaf(), Equals(true));
        });

        it("basic insert", [&]() {
            c->addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255), c));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(0, 0, 0))));
        });

        it("simple insert", [&]() {
            Voxel v(cvec3(1, 1, 1), cvec3(255, 255, 255), c);

            c->addVoxel(Voxel(cvec3(1, 1, 1), cvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(1, 1, 1))));

            c->addVoxel(Voxel(cvec3(5, 1, 1), cvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));

            c->addVoxel(Voxel(cvec3(2, 5, 5), cvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));
        });

        it("is moved when the cluster moves", [&]() {
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(0), glm::vec3(0.01, 0.01, 0.01)));

            c->transform().move(glm::vec3(4, 3, 2));
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(4, 3, 2), glm::vec3(0.01, 0.01, 0.01)));

            c->transform().move(glm::vec3(1, 2, 3));
            c->transform().move(glm::vec3(-1, 2, 2));
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(4, 7, 7), glm::vec3(0.01, 0.01, 0.01)));
        });

        it("can adjust its center", [&]() {
            WorldTreeCluster *d = new WorldTreeCluster(glm::vec3(1, 1, 1));

            AssertThat(d->voxeltree().boundingSphere().position(), EqualsWithDelta(glm::vec3(-1, -1, -1), glm::vec3(0.01, 0.01, 0.01)));
        });

        it("can adjust its center and scale", [&]() {
            WorldTreeCluster *d = new WorldTreeCluster(glm::vec3(1, 1, 1), 3);

            AssertThat(d->voxeltree().boundingSphere().position(), EqualsWithDelta(glm::vec3(-3, -3, -3), glm::vec3(0.01, 0.01, 0.01)));
        });

        // skip until is is clear what this test is supposed to test :)
        it_skip("initially positions all subnodes right", [&]() {
            WorldTreeCluster *d = new WorldTreeCluster(glm::vec3(1, 1, 1), 6);

            d->addVoxel(Voxel(cvec3(1, 1, 1), cvec3(255, 255, 255), c)); // There are 8 subnodes now

            for(VoxeltreeNode *subnode : d->voxeltree().subnodes()) {
                float distance = glm::length(subnode->boundingSphere().position());
                AssertThat(distance, EqualsWithDelta(5.2, 0.01)); // what is supposed to happen here?
            }
        });

        it("supports basic rotation with voxel in center", [&]() {
            glm::vec3 v;
            VoxeltreeNode *n = nullptr;

            c->addVoxel(Voxel(cvec3(1, 1, 1), cvec3(255, 255, 255), c));
            c->transform().setCenter(glm::vec3(1, 1, 1));

            for (VoxeltreeNode *subnode : c->voxeltree().subnodes()) {
                if (subnode->voxel() != nullptr) {
                    n = subnode;
                }
            }
            assert(n != nullptr);

            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0,0,0), glm::vec3(0.01, 0.01, 0.01)));

            c->transform().rotate(glm::angleAxis((float)90.0, glm::vec3(1, 0, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0, 0, 0), glm::vec3(0.01, 0.01, 0.01)));

        });

        it("supports basic rotation with voxel out of center", [&]() {
            glm::vec3 v;
            VoxeltreeNode *n = nullptr;

            c->addVoxel(Voxel(cvec3(1,1,1), cvec3(255, 255, 255), c));
            c->transform().setCenter(glm::vec3(1,1,0));

            for(VoxeltreeNode *subnode : c->voxeltree().subnodes()) {
                if(subnode->voxel() != nullptr) {
                    n = subnode;
                }
            }
            assert(n != nullptr);

            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0,0,1), glm::vec3(0.01, 0.01, 0.01)));

            c->transform().rotate(glm::angleAxis((float)90.0, glm::vec3(1, 0, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0, -1, 0), glm::vec3(0.01, 0.01, 0.01)));

            c->transform().rotate(glm::angleAxis((float)90.0f, glm::vec3(0, 1, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(1, 0, 0), glm::vec3(0.01, 0.01, 0.01)));

        });
    });
});

