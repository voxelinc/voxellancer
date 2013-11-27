#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "worldTree/worldTree.h"
#include "voxel/voxel.h"
#include "voxel/collidablevoxelcluster.h"
#include "collision/collisiondetector.h"



using namespace bandit;


go_bandit([](){
    describe("CollisionDetector", [](){
        WorldTree *worldTree;
        CollidableVoxelCluster *a, *b;
        CollisionDetector *d;


        before_each([&](){
            worldTree = new WorldTree;
            a = new CollidableVoxelCluster(); worldTree->insert(a);
            b = new CollidableVoxelCluster(); worldTree->insert(b);
            d = new CollisionDetector(*worldTree, *a);
        });

        it("works in most basic conditions", [&]() {
            a->addVoxel(new Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));

            AssertThat(d->checkCollisions().size(), Equals(1));

            b->transform().move(glm::vec3(2, 0, 0));

            AssertThat(d->checkCollisions().size(), Equals(0));
        });

        it("works in pretty basic conditions", [&]() {
            a->addVoxel(new Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(cvec3(1, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(cvec3(2, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(cvec3(3, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(cvec3(4, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(cvec3(4, 0, 1), cvec3(255, 255, 255)));

            b->addVoxel(new Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(cvec3(0, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(cvec3(1, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(cvec3(2, 0, 1), cvec3(255, 255, 255)));

            AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(2, 0, 0));
            b->updateGeode();
            AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(0, -2, 0));
            b->updateGeode();
            AssertThat(d->checkCollisions().size(), Equals(0));
        });
    });
});

