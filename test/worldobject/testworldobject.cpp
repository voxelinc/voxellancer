#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "voxel/voxel.h"


using namespace bandit;


go_bandit([](){
    describe("AABB", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");


        before_each([&](){
        });

        it("works in worldobject", [&]() {
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(4, 0, 0), 0xFFFFFF));
            AssertThat(a.aabb().contains(glm::vec3(4.49, 0, 0)), Equals(true));

            a.setPosition(glm::vec3(5, 0, 0));
            AssertThat(a.aabb().contains(glm::vec3(9.49, 0, 0)), Equals(true));
        });

        it("works in rotated  worldobject", [&]() {
            WorldObject a;
            a.addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(4, 0, 0), 0xFFFFFF));

            a.rotate(glm::angleAxis(90.f, glm::vec3(0, 1, 0)));

            AssertThat(a.aabb().contains(glm::vec3(0, 0, -4.49)), Equals(true));
        });

        it("incremental mass and center calculation works", [&]() {
            WorldObject a(0.8f);
            WorldObject b(0.8f);

            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 1, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 2, 0), 0xFFFFFF));
            a.finishInitialization();
            a.removeVoxel(a.voxel(glm::ivec3(3, 2, 0)));

            b.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(3, 1, 0), 0xFFFFFF));
            b.finishInitialization();

            AssertThat(a.physics().mass(), Equals(b.physics().mass()));
            AssertThat(a.physics().physicalCenter(), EqualsWithDelta(b.physics().physicalCenter(), glm::vec3(0.01)));
        });
    });
});

