#include <bandit/bandit.h>

#include <list>
#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include <glowutils/AutoTimer.h>

#include "test/bandit_extension/vec3helper.h"

#include "geometry/acceleration.h"
#include "ui/objectinfo.h"
#include "utils/tostring.h"
#include "physics/physics.h"
#include "resource/clustercache.h"
#include "sound/soundmanager.h"
#include "voxel/voxel.h"
#include "world/world.h"
#include "worldobject/worldobject.h"
#include "worldobject/ship.h"
#include "world/handler/splitdetector.h"
#include "world/helper/worldobjectmodification.h"
#include "world/god.h"
#include "worldobject/worldobjectcomponents.h"



using namespace bandit;

static WorldObject* createPlanet(int diameter)
{
    WorldObject* planet = new WorldObject();
    glm::vec3 middle(diameter / 2, diameter / 2, diameter / 2);
    for (int x = 0; x < diameter; x++) {
        for (int y = 0; y < diameter; y++) {
            for (int z = 0; z < diameter; z++) {
                glm::vec3 cell(x, y, z);

                if (glm::length(cell - middle) < diameter / 2) {
                    planet->addVoxel(new Voxel(glm::ivec3(x, y, z), 0x0055AA));
                }
            }
        }
    }
    planet->setCrucialVoxel(glm::ivec3(middle));
    planet->objectInfo().setName("Planet");	return planet;
}

static void doSplitDetection(WorldObject* planet, WorldObjectModification &mod, int assumedSplits)
{
    glow::debug("remaining voxel: %; removed voxels: %;", planet->voxelCount(), mod.removedVoxels().size());
    std::list<WorldObjectModification> mods{ mod };

    SplitDetector t;
    {
        glowutils::AutoTimer a("20x split detection");
        for (int i = 0; i < 20; i++) {
            t.searchSplitOffs(mods);
        }
    }
    AssertThat(t.splitDataList().size(), Equals(assumedSplits));
}

go_bandit([](){
    describe("VoxelTree", [](){
        World *world;
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");
        SoundManager soundManager;

        before_each([&]() {
            World::reset();
            world = World::instance();
        });

        after_each([&]() {
        });

        it_skip("test a big hole", [&]() {
            WorldObject* planet;

            int diameter = 36;
            planet = createPlanet(diameter);

            // make a circular hole
            WorldObjectModification mod(planet);
            glm::ivec3 centerOfHole(4, diameter / 2, 0);
            int diameterOfHole = 22;

            for (int x = -diameterOfHole / 2; x < diameterOfHole / 2; x++) {
                for (int y = -diameterOfHole / 2; y < diameterOfHole / 2; y++) {
                    for (int z = -diameterOfHole / 2; z < diameterOfHole / 2; z++) {
                        glm::ivec3 cell = centerOfHole + glm::ivec3(x, y, z);
                        if (glm::length(glm::vec3(cell - centerOfHole)) <= diameterOfHole / 2) {
                            Voxel* v = planet->voxel(cell);
                            if (v) {
                                mod.removedVoxel(cell);
                                planet->removeVoxel(v);
                            }
                        }
                    }
                }
            }

            doSplitDetection(planet, mod, 0);
        });

        it_skip("test a split by a plane", [&]() {
            WorldObject* planet;

            int diameter = 36;
            planet = createPlanet(diameter);

            // make a plane split
            WorldObjectModification mod(planet);

            for (int x = 0; x < diameter; x++) {
                for (int y = 0; y < diameter; y++) {
                    glm::ivec3 cell = glm::ivec3(x, y, diameter / 2);
                    Voxel* v = planet->voxel(cell);
                    if (v) {
                        mod.removedVoxel(cell);
                        planet->removeVoxel(v);
                    }
                }
            }

            doSplitDetection(planet, mod, 1);
        });


        it("test global performance", [&]() {
            Ship *ship;
            Ship *normandy;
            WorldObject *planet;
            {
                glowutils::AutoTimer t("init perftest");

                normandy = new Ship();
                ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
                normandy->transform().setPosition(glm::vec3(0, 0, -100));
                normandy->objectInfo().setName("Normandy");
                World::instance()->god().scheduleSpawn(normandy);

                ship = new Ship();
                ClusterCache::instance()->fillObject(ship, "data/voxelcluster/basicship.csv");
                ship->transform().setPosition(glm::vec3(0, 0, 10));
                ship->objectInfo().setName("basicship");
                ship->objectInfo().setShowOnHud(false);
                World::instance()->god().scheduleSpawn(ship);

                WorldObject *wall = new WorldObject();
                wall->transform().move(glm::vec3(-20, 0, -50));
                wall->transform().rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));

                for (int x = 0; x < 20; x++) {
                    for (int y = 0; y < 15; y++) {
                        for (int z = 0; z < 3; z++) {
                            wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
                        }
                    }
                }
                wall->objectInfo().setName("Wall");
                World::instance()->god().scheduleSpawn(wall);

                planet = createPlanet(28);
                planet->transform().move(glm::vec3(20, 10, -130));
                World::instance()->god().scheduleSpawn(planet);

                glow::debug("Initial spawn");
                World::instance()->god().spawn();
            }
            normandy->physics().setAcceleration(Acceleration(glm::vec3(0, 0, 1), glm::vec3(0.0f)));
            ship->physics().setAcceleration(Acceleration(glm::vec3(0, 0, 1), glm::vec3(0.0f)));
            {
                glowutils::AutoTimer t("simulation");
                for (int i = 0; i < 1000; i++) {
                    ship->setTargetObject(planet);
                    //ship->fireAtObject();
                    ship->components().fireAtPoint(planet->transform().position());
                    World::instance()->update(0.016f);
                }
            }
            glow::debug("simulation done");
        });
    });
});

