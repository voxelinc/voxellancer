#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "worldtree/worldtree.h"
#include "voxel/voxel.h"
#include "physics/physicalvoxel.h"
#include "physics/physicalvoxelcluster.h"
#include "collision/collisiondetector.h"



using namespace bandit;


go_bandit([](){
    describe("CollisionDetector", [](){
        WorldTree *worldTree;
        PhysicalVoxelCluster *a, *b;
        CollisionDetector *d;


        before_each([&](){
            worldTree = new WorldTree;
            a = new c(); worldTree->insert(a);
            b = new PhysicalVoxelCluster(); worldTree->insert(b);
            d = new CollisionDetector(*worldTree, *a);
        });

        it("works in most basic conditions", [&]() {
            a->addVoxel(new PhysicalVoxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new PhysicalVoxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));

            AssertThat(d->checkCollisions().size(), Equals(1));

            b->transform().move(glm::vec3(2, 0, 0));

            AssertThat(d->checkCollisions().size(), Equals(0));
        });

        it("works in pretty basic conditions", [&]() {
            a->addVoxel(new PhysicalVoxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new PhysicalVoxel(cvec3(1, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new PhysicalVoxel(cvec3(2, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new PhysicalVoxel(cvec3(3, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new PhysicalVoxel(cvec3(4, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new PhysicalVoxel(cvec3(4, 0, 1), cvec3(255, 255, 255)));

            b->addVoxel(new PhysicalVoxel(cvec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new PhysicalVoxel(cvec3(0, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new PhysicalVoxel(cvec3(1, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new PhysicalVoxel(cvec3(2, 0, 1), cvec3(255, 255, 255)));

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

