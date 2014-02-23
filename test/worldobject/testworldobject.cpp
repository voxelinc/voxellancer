#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"
#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "voxel/voxel.h"
#include "voxel/voxeltreenode.h"
#include "voxel/voxelclusterbounds.h"
#include "physics/physics.h"


using namespace bandit;


go_bandit([](){
    describe("AABB", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&](){
        });

        it("works in worldobject", [&]() {
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(4, 0, 0), 0xFFFFFF));
            AssertThat(a.bounds().aabb().contains(glm::vec3(4.49, 0, 0)), Equals(true));
            AssertThat(a.transform().position(), EqualsWithDelta(glm::vec3(2, 0, 0), glm::vec3(0.01, 0.01, 0.01)));

            a.transform().setPosition(glm::vec3(7, 0, 0));
            AssertThat(a.bounds().aabb().contains(glm::vec3(9.49, 0, 0)), Equals(true));
        });


        it("incremental mass calculation works", [&]() {
            WorldObject a;
            WorldObject b;
            a.transform().setScale(0.8f);
            b.transform().setScale(0.8f);

            a.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 1, 0), 0xFFFFFF));
            a.addVoxel(new Voxel(glm::ivec3(3, 2, 0), 0xFFFFFF));
            a.removeVoxel(a.voxel(glm::ivec3(3, 2, 0)));

            b.addVoxel(new Voxel(glm::ivec3(1, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(2, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(3, 0, 0), 0xFFFFFF));
            b.addVoxel(new Voxel(glm::ivec3(3, 1, 0), 0xFFFFFF));

            AssertThat(a.physics().mass(), Equals(b.physics().mass()));
            AssertThat(a.transform().center(), EqualsWithDelta(b.transform().center(), glm::vec3(0.01)));
        });
    });
});

