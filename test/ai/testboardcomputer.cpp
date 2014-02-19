#include <bandit/bandit.h>

#include <iostream>

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"
#include "physics/physics.h"



using namespace bandit;


go_bandit([](){
    describe("boardComputer", [](){

        Ship* ship;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");


        before_each([&](){
            ship = new Ship();
            ship->transform().setPosition(glm::vec3(0, 0, 0));
        });

        it("moves in the right direction", [&]() {
            ship->boardComputer()->moveTo(glm::vec3(1, 0, 0));
            ship->boardComputer()->update(0.1f);
            AssertThat(ship->boardComputer()->engineState().directional().x, IsGreaterThan(0));
            AssertThat(ship->boardComputer()->engineState().directional().y, Equals(0));
            AssertThat(ship->boardComputer()->engineState().directional().z, Equals(0));
        });

        it("rotates in the right direction", [&]() {
            // ship looks in -z by default
            ship->boardComputer()->rotateTo(glm::vec3(0, 1, 0));
            ship->boardComputer()->update(0.1f);
            AssertThat(ship->boardComputer()->engineState().angular().x, IsGreaterThan(0));
            AssertThat(ship->boardComputer()->engineState().angular().y, Equals(0));
            AssertThat(ship->boardComputer()->engineState().angular().z, Equals(0));
        });

        it("doesnt rotate when already nearly rotated", [&]() {
            ship->boardComputer()->rotateTo(glm::vec3(0, 0.01, -1));
            ship->boardComputer()->update(0.1f);
            AssertThat(ship->boardComputer()->engineState().angular().x, Equals(0));
            AssertThat(ship->boardComputer()->engineState().angular().y, Equals(0));
            AssertThat(ship->boardComputer()->engineState().angular().z, Equals(0));
        });

    });
});

