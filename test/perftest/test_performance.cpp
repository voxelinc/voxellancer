#include <bandit/bandit.h>

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "glow/AutoTimer.h"

#include "utils/tostring.h"
#include "world/world.h"
#include "worldobject/worldobject.h"
#include "../bandit_extension/vec3helper.h"
#include "worldobject/ship.h"
#include "resource/clustercache.h"

using namespace bandit;

go_bandit([](){
    describe("VoxelTree", [](){
        World *world;
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&]() {
            World::reset();
            world = World::instance();
        });

        after_each([&]() {
        });
        
       
        it("test performance, unskip for testing", [&]() {
            Ship *ship;
            Ship *normandy;            
            WorldObject *planet;
            {
                glow::AutoTimer t("init perftest");

                normandy = new Ship();
                ClusterCache::instance()->fillObject(normandy, "data/voxelcluster/normandy.csv");
                normandy->setPosition(glm::vec3(0, 0, -100));
                normandy->objectInfo().setName("Normandy");
                World::instance()->god().scheduleSpawn(normandy);

                ship = new Ship();
                ClusterCache::instance()->fillObject(ship, "data/voxelcluster/basicship.csv");
                ship->setPosition(glm::vec3(0, 0, 10));
                ship->objectInfo().setName("basicship");
                ship->objectInfo().setShowOnHud(false);
                World::instance()->god().scheduleSpawn(ship);

                WorldObject *wall = new WorldObject(1);
                wall->move(glm::vec3(-20, 0, -50));
                wall->rotate(glm::angleAxis(-90.f, glm::vec3(0, 1, 0)));
                for (int x = 0; x < 20; x++) {
                    for (int y = 0; y < 15; y++) {
                        for (int z = 0; z < 3; z++) {
                            wall->addVoxel(new Voxel(glm::ivec3(z, x, y), 0xB47878));
                        }
                    }
                }
                wall->objectInfo().setName("Wall");
                World::instance()->god().scheduleSpawn(wall);

                planet = new WorldObject();
                planet->move(glm::vec3(20, 10, -130));
                int diameter = 28;
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
                planet->objectInfo().setName("Planet");
                World::instance()->god().scheduleSpawn(planet);

                glow::debug("Initial spawn");
                World::instance()->god().spawn();
            }
            normandy->accelerate(glm::vec3(0, 0, 1));
            ship->accelerate(glm::vec3(0, 0, 1));
            {
                glow::AutoTimer t("simulation");
                for (int i = 0; i < 10000; i++) {
                    ship->setTargetObject(planet);
                    ship->fireAtObject();
                    //ship->fireAtPoint(planet->transform().position());
                    World::instance()->update(0.016f);
                }
            }
            glow::debug("simulation done");
        });
    });
});

