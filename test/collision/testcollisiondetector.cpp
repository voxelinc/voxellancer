#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "worldtree/worldtree.h"
#include "voxel/voxel.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"
#include "world/world.h"
#include "world/god.h"
#include "../bandit_extension/aabbhelper.h"



using namespace bandit;


go_bandit([](){
    describe("CollisionDetector", [](){
        World *world;
        WorldObject *a, *b;
        CollisionDetector *d;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&](){
            world = new World();
            a = new WorldObject(); world->god().scheduleSpawn(a);
            b = new WorldObject(); world->god().scheduleSpawn(b);
            d = &a->collisionDetector();
            world->god().spawn();
        });

        it("works in most basic conditions", [&]() {
            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));

         //   AssertThat(d->checkCollisions().size(), Equals(1));

            b->transform().move(glm::vec3(2, 0, 0));

         //   AssertThat(d->checkCollisions().size(), Equals(0));
        });

        it("works in pretty basic conditions", [&]() {
            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a->addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a->addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a->addVoxel(new Voxel(glm::ivec3(4, 0, 0), 0xFFFFFF));
            a->addVoxel(new Voxel(glm::ivec3(4, 0, 1), 0xFFFFFF));

            b->addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 1), 0xFFFFFF));
            b->addVoxel(new Voxel(glm::ivec3(1, 0, 1), 0xFFFFFF));
            b->addVoxel(new Voxel(glm::ivec3(2, 0, 1), 0xFFFFFF));

          //  AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(2, 0, 0));
            b->collisionDetector().updateGeode();
        //    AssertThat(d->checkCollisions().size(), IsGreaterThan(0));

            b->transform().move(glm::vec3(0, -2, 0));
            b->collisionDetector().updateGeode();
           // AssertThat(d->checkCollisions().size(), Equals(0));
        });


        it("aabb shrinkLeft", [&]() {
            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0)));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0)));
            AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(1,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(0, 0, 0)));
            AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(1,0,0), glm::ivec3(1,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(1, 0, 0)));
            AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));

        });

        it("aabb resize on voxel add/remove", [&]() {
            AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));

            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(3, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(2, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(2, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->removeVoxel(a->voxel(glm::ivec3(3, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(IAABB(glm::ivec3(0,0,0), glm::ivec3(1,0,0))));

        });
    });
});

