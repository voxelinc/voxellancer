#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "voxel/voxelcluster.h"
#include "voxel/voxeltreenode.h"

#include "utils/tostring.h"


using namespace bandit;

bool operator>=(const glm::vec3 &a, const glm::vec3 &b) {
    return a.x >= b.x && a.y >= b.y && a.z >= b.z;
}

bool operator<=(const glm::vec3 &a, const glm::vec3 &b) {
    return a.x <= b.x && a.y <= b.y && a.z <= b.z;
}

go_bandit([](){
    describe("Voxeltree", [](){
        VoxelCluster *c;
        VoxeltreeNode *r;

        before_each([&]() {
            c = new VoxelCluster();
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
            c->addVoxel(Voxel(cvec3(0, 0, 0), ucvec3(255, 255, 255), c));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(0, 0, 0))));
        });

        it("simple insert", [&]() {
            Voxel v(cvec3(1, 1, 1), ucvec3(255, 255, 255), c);

            c->addVoxel(Voxel(cvec3(1, 1, 1), ucvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(1, 1, 1))));

            c->addVoxel(Voxel(cvec3(5, 1, 1), ucvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));

            c->addVoxel(Voxel(cvec3(2, 5, 5), ucvec3(255, 255, 255), c));
            AssertThat(r->subnodes().size(), Equals(8));
            AssertThat(r->gridAABB(), Equals(Grid3dAABB(glm::ivec3(0,0,0), glm::ivec3(7, 7, 7))));
        });

        it("is moved when the cluster moves", [&]() {
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.05, 0.05, 0.05)));

            c->transform(glm::vec3(4, 3, 2));
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(4.5, 3.5, 2.5), glm::vec3(0.05, 0.05, 0.05)));

            c->transform(glm::vec3(1, 2, 3));
            c->transform(glm::vec3(-1, 2, 2));
            AssertThat(r->boundingSphere().position(), EqualsWithDelta(glm::vec3(4.5, 7.5, 7.5), glm::vec3(0.05, 0.05, 0.05)));
        });

        it("can adjust its center", [&]() {
            VoxelCluster *d = new VoxelCluster(3);
            d->setCenterInGrid(glm::vec3(1.5, 1.5, 1.5));

            AssertThat(d->voxeltree().boundingSphere().position(), EqualsWithDelta(glm::vec3(0, 0, 0), glm::vec3(0.05, 0.05, 0.05)));
        });

        it("initially positions all subnodes right", [&]() {
            VoxelCluster *d = new VoxelCluster(6);
            d->setCenterInGrid(glm::vec3(6, 6, 6));

            d->addVoxel(Voxel(cvec3(1, 1, 1), ucvec3(255, 255, 255), c)); // There are 8 subnodes now

            for(VoxeltreeNode *subnode : d->voxeltree().subnodes()) {
                float distance = glm::length(subnode->boundingSphere().position());
                AssertThat(distance, EqualsWithDelta(5.2, 0.1));
            }
        });

        it("supports basic rotation without translation", [&]() {
            glm::vec3 v;
            VoxeltreeNode *n = nullptr;

            c->addVoxel(Voxel(cvec3(1,1,1), ucvec3(255, 255, 255), c));
            c->setCenterInGrid(glm::vec3(1,1,1));

            for(VoxeltreeNode *subnode : c->voxeltree().subnodes()) {
                if(subnode->voxel() != nullptr) {
                    n = subnode;
                }
            }
            assert(n != nullptr);

            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.05, 0.05, 0.05)));

            c->transform(glm::angleAxis((float)90.0, glm::vec3(1, 0, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0.05, 0.05, 0.05)));

            c->transform(glm::angleAxis((float)90.0f, glm::vec3(0, 1, 0)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.05, 0.05, 0.05)));

            c->transform(glm::angleAxis((float)90.0, glm::vec3(0, 0, -1)));
            AssertThat(n->boundingSphere().position(), EqualsWithDelta(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0.05, 0.05, 0.05)));
        });
    });
});

