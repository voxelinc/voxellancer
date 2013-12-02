#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "../bandit_extension/vec3helper.h"
#include "world/worldobject.h"
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
            a.addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(4, 0, 0), cvec3()));
            AssertThat(a.aabb().contains(glm::vec3(4.49, 0, 0)), Equals(true));
            
            a.transform().moveWorld(glm::vec3(5, 0, 0));
            AssertThat(a.aabb().contains(glm::vec3(9.49, 0, 0)), Equals(true));
        });

        it("works in rotated  worldobject", [&]() {
            WorldObject a;
            a.addVoxel(new Voxel(glm::ivec3(0, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), cvec3()));
            a.addVoxel(new Voxel(glm::ivec3(4, 0, 0), cvec3()));

            a.transform().rotate(glm::angleAxis(90.f, glm::vec3(0, 1, 0)));

            AssertThat(a.aabb().contains(glm::vec3(0, 0, -4.49)), Equals(true));
        });
    });
});

