#include <bandit/bandit.h>

#include <iostream>

#include "worldobject/ship.h"




using namespace bandit;


go_bandit([](){
    describe("boardComputer", [](){

        Ship* ship;
 
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        before_each([&](){
            ship = new Ship();
            ship->setPosition(glm::vec3(0, 0, 0));
        });

        it("moves in the right direction", [&]() {
            ship->boardComputer()->moveTo(glm::vec3(1, 0, 0), 0);
            AssertThat(ship->physics().acceleration().x, IsGreaterThan(0));
            AssertThat(ship->physics().acceleration().y, Equals(0));
            AssertThat(ship->physics().acceleration().z, Equals(0));
        });

        it("rotates in the right direction", [&]() {
            // ship looks in -z by default
            ship->boardComputer()->rotateTo(glm::vec3(0, 1, 0));
            AssertThat(ship->physics().angularAcceleration().x, IsGreaterThan(0));
            AssertThat(ship->physics().angularAcceleration().y, Equals(0));
            AssertThat(ship->physics().angularAcceleration().z, Equals(0));
        });

        it("doesnt rotate when already nearly rotated", [&]() {
            ship->boardComputer()->rotateTo(glm::vec3(0, 0.01, -1));
            AssertThat(ship->physics().angularAcceleration().x, Equals(0));
            AssertThat(ship->physics().angularAcceleration().y, Equals(0));
            AssertThat(ship->physics().angularAcceleration().z, Equals(0));
        });

    });
});

