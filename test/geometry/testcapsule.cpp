#include <bandit/bandit.h>

#include <iostream>

#include "geometry/capsule.h"

#include "../bandit_extension/vec3helper.h"


using namespace bandit;


go_bandit([](){
    describe("Capsule", [](){

        before_each([&](){
        });

        it("intersects", [&]() {
            Capsule c(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 1.0f);
            Sphere s(glm::vec3(0, 1, 0), 1.2f);

            AssertThat(c.intersects(s), Equals(true));
        });

        it("does not intersect", [&]() {
            Capsule c(glm::vec3(0, -1, 0), glm::vec3(0, 2, 0), 0.5f);
            Sphere s(glm::vec3(1, 2, 0), 0.4f);

            AssertThat(c.intersects(s), Equals(false));
        });

        it("is nearTo", [&](){
            Capsule c(glm::vec3(-2, -2, -2), glm::vec3(4, 4, 4), 1.0f);
            IAABB a(glm::ivec3(-1, 0, -1), glm::ivec3(1, 1, 0));

            AssertThat(c.nearTo(a), Equals(true));
        });

        it("is not nearTo", [&](){
            Capsule c(glm::vec3(-2, -2, -2), glm::vec3(0, 4, 4), 0.6f);
            IAABB a(glm::ivec3(-1, 0, -1), glm::ivec3(1, 1, 0));

            AssertThat(c.nearTo(a), Equals(false));
        });

        it("is containedBy", [&](){
            Capsule c(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), 1.7f);
            IAABB a(glm::ivec3(-3, -3, -3), glm::ivec3(2, 2, 2));

            AssertThat(c.containedBy(a), Equals(true));
        });

        it("is not containedBy", [&](){
            Capsule c(glm::vec3(-1, 2, 0), glm::vec3(3, 0, 0), 0.5f);
            IAABB a(glm::ivec3(-2, -2, -2), glm::ivec3(3, 2, 1));

            AssertThat(c.containedBy(a), Equals(false));
        });

    });
});

