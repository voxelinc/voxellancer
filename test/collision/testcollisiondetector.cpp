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
        World *world;
        WorldObject *a, *b;
        CollisionDetector *d;


        before_each([&](){
            world = new World();
            a = new WorldObject(); world->god()->scheduleSpawn(a);
            b = new WorldObject(); world->god()->scheduleSpawn(b);
            d = &a->physics().collisionDetector();
            world->god()->spawn();
        });

        it("works in most basic conditions", [&]() {
            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3(255, 255, 255)));

            AssertThat(d->checkCollisions().size(), Equals(1));

            b->transform().move(glm::vec3(2, 0, 0));

            AssertThat(d->checkCollisions().size(), Equals(0));
        });

        it("works in pretty basic conditions", [&]() {
            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(glm::ivec3(2, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(glm::ivec3(3, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(glm::ivec3(4, 0, 0), cvec3(255, 255, 255)));
            a->addVoxel(new Voxel(glm::ivec3(4, 0, 1), cvec3(255, 255, 255)));

            b->addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(glm::ivec3(1, 0, 1), cvec3(255, 255, 255)));
            b->addVoxel(new Voxel(glm::ivec3(2, 0, 1), cvec3(255, 255, 255)));

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

