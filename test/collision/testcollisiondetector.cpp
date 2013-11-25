#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "worldtree/worldtree.h"
#include "voxel/voxel.h"
#include "collision/collisiondetector.h"
#include "world/physicalvoxelcluster.h"



using namespace bandit;


go_bandit([](){
    describe("CollisionDetector", [](){
        Worldtree *worldtree;
        PhysicalVoxelCluster *a, *b;
        CollisionDetector *d;


        before_each([&](){
            worldtree = new Worldtree;
            a = new PhysicalVoxelCluster(); worldtree->insert(a);
            b = new PhysicalVoxelCluster(); worldtree->insert(b);
            d = new CollisionDetector(*worldtree, *a);
        });

        it("works in most basic conditions", [&]() {
            a->addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255), a));
            b->addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255), b));

            AssertThat(d->checkCollisions().size(), Equals(1));

            b->transform().move(glm::vec3(2, 0, 0));

            AssertThat(d->checkCollisions().size(), Equals(0));
        });

        it("works in pretty basic conditions", [&]() {
            a->addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255), a));
            a->addVoxel(Voxel(cvec3(1, 0, 0), cvec3(255, 255, 255), a));
            a->addVoxel(Voxel(cvec3(2, 0, 0), cvec3(255, 255, 255), a));
            a->addVoxel(Voxel(cvec3(3, 0, 0), cvec3(255, 255, 255), a));
            a->addVoxel(Voxel(cvec3(4, 0, 0), cvec3(255, 255, 255), a));
            a->addVoxel(Voxel(cvec3(4, 0, 1), cvec3(255, 255, 255), a));

            b->addVoxel(Voxel(cvec3(0, 0, 0), cvec3(255, 255, 255), b));
            b->addVoxel(Voxel(cvec3(0, 0, 1), cvec3(255, 255, 255), b));
            b->addVoxel(Voxel(cvec3(1, 0, 1), cvec3(255, 255, 255), b));
            b->addVoxel(Voxel(cvec3(2, 0, 1), cvec3(255, 255, 255), b));

            AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(2, 0, 0));
            b->applyTransform(false);
            AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(0, -2, 0));
            b->applyTransform(false);
            AssertThat(d->checkCollisions().size(), Equals(0));
        });
    });
});

