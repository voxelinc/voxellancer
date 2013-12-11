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

            b->setPosition(glm::vec3(4, 0, 0));
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
            Impulse i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 0, 0), 1.0);

            std::list<Impulse> impulses{i};

            df->forwardDamageImpulses(impulses);

            AssertThat(df->forwardedDamageImpulses().size(), Equals(1));

            Impulse f = df->forwardedDamageImpulses().front();
            AssertThat(f.speed(), EqualsWithDelta(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
        });

        it("Negative direction test", [&] {
            Impulse i(a, a->voxel(glm::ivec3(2, 0, 0)), glm::vec3(-2, 0, 0), 1.0);

            std::list<Impulse> impulses{i};

            df->forwardDamageImpulses(impulses);

            AssertThat(df->forwardedDamageImpulses().size(), Equals(1));

            Impulse f = df->forwardedDamageImpulses().front();
            AssertThat(f.speed(), EqualsWithDelta(glm::vec3(-2.0, 0.0, 0.0), glm::vec3(0.1, 0.1, 0.1)));
            AssertThat(f.voxel(), Equals(a->voxel(glm::ivec3(1, 0, 0))));
        });

        it("Z Axis Test", [&] {

            Impulse i1(b, b->voxel(glm::ivec3(0, 0, 0)), glm::vec3(0, 0, 5), 1.0);
            Impulse i2(b, b->voxel(glm::ivec3(0, 0, 3)), glm::vec3(0, 0, -3), 1.0);

            std::list<Impulse> impulses{i1, i2};

            df->forwardDamageImpulses(impulses);

            AssertThat(df->forwardedDamageImpulses().size(), Equals(2));

            Impulse f1 = df->forwardedDamageImpulses().front();
            Impulse f2 = df->forwardedDamageImpulses().back();
            AssertThat(f1.speed(), EqualsWithDelta(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.1, 0.1, 0.1)));
            AssertThat(f2.speed(), EqualsWithDelta(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.1, 0.1, 0.1)));
        });

        it("Forwarding from angle != perpendicular", [&] {
            Impulse i(a, a->voxel(glm::ivec3(0, 0, 0)), glm::vec3(1, 1, 0), 1.0);

            std::list<Impulse> impulses{i};

            df->forwardDamageImpulses(impulses);


            Impulse f = df->forwardedDamageImpulses().front();

            AssertThat(glm::length(f.speed()), EqualsWithDelta(glm::length(i.speed()) / 2.0, 0.05));
            AssertThat(glm::normalize(f.speed()), EqualsWithDelta(glm::normalize(i.speed()), glm::vec3(0.1, 0.1, 0.1)));
        });
    });
});
}

