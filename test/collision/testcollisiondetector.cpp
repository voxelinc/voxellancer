#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "worldtree/worldtree.h"
#include "voxel/voxel.h"
#include "collision/collisiondetector.h"
#include "worldobject/worldobject.h"
#include "../bandit_extension/aabbhelper.h"
#include "voxel/voxelclusterbounds.h"




using namespace bandit;


go_bandit([](){
    describe("CollisionDetector", [](){
        std::shared_ptr<Universe> m_universe;
        std::shared_ptr<Sector> m_sector;
        WorldObject *a, *b;
        CollisionDetector *d;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&](){
            m_universe.reset(new Universe());
            m_sector.reset(new Sector("bla", m_universe.get()));

            a = new WorldObject(); a->setUniverse(m_universe.get()); a->setSector(m_sector.get()); a->spawn();
            b = new WorldObject(); b->setUniverse(m_universe.get()); b->setSector(m_sector.get()); b->spawn();

            d = &a->collisionDetector();
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
            AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(1,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(0, 0, 0)));
            AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(1,0,0), glm::ivec3(1,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(1, 0, 0)));
            AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));

        });

        it("aabb resize on voxel add/remove", [&]() {
            AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));

            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(0,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(3, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(2, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));

            a->removeVoxel(a->voxel(glm::ivec3(2, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(3,0,0))));
            a->removeVoxel(a->voxel(glm::ivec3(3, 0, 0))); AssertThat(a->bounds().minimalGridAABB(), Equals(GridAABB(glm::ivec3(0,0,0), glm::ivec3(1,0,0))));

        });
    });
});

