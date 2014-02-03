#include <bandit/bandit.h>

#include <iostream>

#include "worldobject/ship.h"
#include "ai/boardcomputer.h"



using namespace bandit;


go_bandit([](){
    describe("boardComputer", [](){

        Ship* ship;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&](){
            ship = new Ship();
            ship->transform().setPosition(glm::vec3(0, 0, 0));
        });

        it("moves in the right direction", [&]() {
            ship->boardComputer()->moveTo(glm::vec3(1, 0, 0));
            AssertThat(ship->physics().acceleration().directional().x, IsGreaterThan(0));
            AssertThat(ship->physics().acceleration().directional().y, Equals(0));
            AssertThat(ship->physics().acceleration().directional().z, Equals(0));
        });

        it("rotates in the right direction", [&]() {
            // ship looks in -z by default
            ship->boardComputer()->rotateTo(glm::vec3(0, 1, 0));
            AssertThat(ship->physics().acceleration().angular().x, IsGreaterThan(0));
            AssertThat(ship->physics().acceleration().angular().y, Equals(0));
            AssertThat(ship->physics().acceleration().angular().z, Equals(0));
        });

        it("doesnt rotate when already nearly rotated", [&]() {
            ship->boardComputer()->rotateTo(glm::vec3(0, 0.01, -1));
            AssertThat(ship->physics().acceleration().angular().x, Equals(0));
            AssertThat(ship->physics().acceleration().angular().y, Equals(0));
            AssertThat(ship->physics().acceleration().angular().z, Equals(0));
        });

    });
});

