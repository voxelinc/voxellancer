#include <bandit/bandit.h>

#include "../bandit_extension/vec3helper.h"

#include "worldobject/worldobject.h"
#include "world/world.h"
#include "world/worldlogic.h"
#include "world/god.h"
#include "world/handler/damageforwarder.h"
#include "voxel/voxel.h"

namespace bandit
{
go_bandit([]() {
    describe("DamageForwarder", [](){
        World* world;
        WorldObject* a;
        WorldObject* b;
        DamageForwarder* df;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&] {
            world = new World();
            a = new WorldObject();
            b = new WorldObject();
            df = &world->worldLogic().damageForwarder();

            a->addVoxel(new Voxel(glm::ivec3(0, 0, 0)));
            a->addVoxel(new Voxel(glm::ivec3(1, 0, 0)));
            a->addVoxel(new Voxel(glm::ivec3(2, 0, 0)));

            b->transform().setPosition(glm::vec3(4, 0, 0));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 0)));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 1)));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 2)));
            b->addVoxel(new Voxel(glm::ivec3(0, 0, 3)));
            b->addVoxel(new Voxel(glm::ivec3(2, 0, 0)));

            world->god().scheduleSpawn(a);
            world->god().scheduleSpawn(b);

            world->god().spawn();
        });

        after_each([&] {
            delete world;
        });

        it("Most basic test", [&] {
            DamageImpact i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 0, 0));

            std::list<DamageImpact> impulses{i};

            df->forwardDamageImpacts(impulses);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(1));

            DamageImpact f = df->forwardedDamageImpacts().front();
            AssertThat(f.damageVec(), EqualsWithDelta(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
        });

        it("Negative direction test", [&] {
            DamageImpact i(a, a->voxel(glm::ivec3(2, 0, 0)), glm::vec3(-2, 0, 0));

            std::list<DamageImpact> impulses{i};

            df->forwardDamageImpacts(impulses);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(1));

            DamageImpact f = df->forwardedDamageImpacts().front();
            AssertThat(f.damageVec(), EqualsWithDelta(glm::vec3(-2.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
            AssertThat(f.voxel(), Equals(a->voxel(glm::ivec3(1, 0, 0))));
        });

        it("Z Axis Test", [&] {
            DamageImpact i1(b, b->voxel(glm::ivec3(0, 0, 0)), glm::vec3(0, 0, 5));
            DamageImpact i2(b, b->voxel(glm::ivec3(0, 0, 3)), glm::vec3(0, 0, -3));

            std::list<DamageImpact> impulses{i1, i2};

            df->forwardDamageImpacts(impulses);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(2));

            DamageImpact f1 = df->forwardedDamageImpacts().back();
            DamageImpact f2 = df->forwardedDamageImpacts().front();

            // there is no guaranty that f1 and f2 are ordered
            if (f1.damageVec().z > f2.damageVec().z) {
                AssertThat(f1.damageVec(), EqualsWithDelta(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.1, 0.1, 0.1)));
                AssertThat(f2.damageVec(), EqualsWithDelta(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.1, 0.1, 0.1)));
            }
            else {
                AssertThat(f2.damageVec(), EqualsWithDelta(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.1, 0.1, 0.1)));
                AssertThat(f1.damageVec(), EqualsWithDelta(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.1, 0.1, 0.1)));
            }
        });

        it("Forwarding from angle != perpendicular", [&] {
            DamageImpact i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 1, 0));

            std::list<DamageImpact> impulses{i};

            df->forwardDamageImpacts(impulses);


            DamageImpact f = df->forwardedDamageImpacts().front();

            AssertThat(glm::length(f.damageVec()), EqualsWithDelta(glm::length(i.damageVec()) / 2.0, 0.05));
            AssertThat(glm::normalize(f.damageVec()), EqualsWithDelta(glm::normalize(i.damageVec()), glm::vec3(0.1, 0.1, 0.1)));
        });
    });
});
}

