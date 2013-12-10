#include <bandit/bandit.h>

#include "../bandit_extension/vec3helper.h"

#include "worldobject/worldobject.h"
#include "world/world.h"
#include "world/worldlogic.h"
#include "world/god.h"
#include "world/handler/damageforwarder.h"

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
            Impact i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 0, 0), 1.0);

            std::list<Impact> impacts{i};

            df->forwardDamageImpacts(impacts);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(1));

            Impact f = df->forwardedDamageImpacts().front();
            AssertThat(f.speed(), EqualsWithDelta(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
        });

        it("Negative direction test", [&] {
            Impact i(a, a->voxel(glm::ivec3(2, 0, 0)), glm::vec3(-2, 0, 0), 1.0);

            std::list<Impact> impacts{i};

            df->forwardDamageImpacts(impacts);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(1));

            Impact f = df->forwardedDamageImpacts().front();
            AssertThat(f.speed(), EqualsWithDelta(glm::vec3(-2.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
            AssertThat(f.voxel(), Equals(a->voxel(glm::ivec3(1, 0, 0))));
        });

        it("Z Axis Test", [&] {

            Impact i1(b, b->voxel(glm::ivec3(0, 0, 0)), glm::vec3(0, 0, 5), 1.0);
            Impact i2(b, b->voxel(glm::ivec3(0, 0, 3)), glm::vec3(0, 0, -3), 1.0);

            std::list<Impact> impacts{i1, i2};

            df->forwardDamageImpacts(impacts);

            AssertThat(df->forwardedDamageImpacts().size(), Equals(2));

            Impact f1 = df->forwardedDamageImpacts().front();
            Impact f2 = df->forwardedDamageImpacts().back();
            AssertThat(f1.speed(), EqualsWithDelta(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.1, 0.1, 0.1)));
            AssertThat(f2.speed(), EqualsWithDelta(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.1, 0.1, 0.1)));
        });

        it("Forwarding from angle != perpendicular", [&] {
            Impact i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 1, 0), 1.0);

            std::list<Impact> impacts{i};

            df->forwardDamageImpacts(impacts);


            Impact f = df->forwardedDamageImpacts().front();

            AssertThat(glm::length(f.speed()), EqualsWithDelta(glm::length(i.speed()) / 2.0, 0.05));
            AssertThat(glm::normalize(f.speed()), EqualsWithDelta(glm::normalize(i.speed()), glm::vec3(0.1, 0.1, 0.1)));
        });
    });
});
}

