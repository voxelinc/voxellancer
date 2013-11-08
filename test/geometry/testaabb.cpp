#include <bandit/bandit.h>

#include <iostream>

#include "geometry/aabb.h"


using namespace bandit;


go_bandit([](){
    describe("AABB", [](){
        before_each([&](){
        });

        it("has correct bounds", [&]() {
           AABB a(glm::vec3(3, -2, 1), glm::vec3(8, 5, 3));

            AssertThat(a.extent(XAxis), Equals(5));
            AssertThat(a.extent(YAxis), Equals(7));
            AssertThat(a.extent(ZAxis), Equals(2));

            AssertThat(a.axisMin(XAxis), Equals(3));
            AssertThat(a.axisMax(XAxis), Equals(8));
            AssertThat(a.axisMin(ZAxis), Equals(1));
            AssertThat(a.axisMax(ZAxis), Equals(3));
            AssertThat(a.axisMax(YAxis), Equals(5));
            AssertThat(a.axisMin(YAxis), Equals(-2));
        });

        it("intersects", [&](){
            AABB a(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
            AABB b(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

            AssertThat(a.intersects(b) && b.intersects(a), Equals(true));

            a.move(XAxis, 1);
            AssertThat(!(a.intersects(b) && b.intersects(a)), Equals(true));

            b.move(XAxis, 0.2);
            AssertThat(a.intersects(b) && b.intersects(a), Equals(true));

            a.move(glm::vec3(-1.5, -0.8, -0.8));
            b.move(glm::vec3(-0.2, 0, 0));
            AssertThat(a.intersects(b) && b.intersects(a), Equals(true));
        });

        it("contains", [&](){
            AABB a(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
            AABB b(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
            AABB c(glm::vec3(0, 0, 0), glm::vec3(0.3, 0.4, 1.5));
            AABB d(glm::vec3(0, 0, 0), glm::vec3(0.3, 0.4, 0.5));
            AABB e(glm::vec3(-1, 0.2, 0.2), glm::vec3(0.3, 0.4, 0.5));

            AssertThat(a.contains(b) && b.contains(a), Equals(true));
            AssertThat(!a.contains(c), Equals(true));
            AssertThat(!a.contains(e), Equals(true));
            AssertThat(a.contains(d), Equals(true));

    a.move(XAxis, 0.1f);
            AssertThat(!(a.contains(b) && b.contains(a)), Equals(true));

            d.move(glm::vec3(0.2, 0.4, 0.1));
            AssertThat(a.contains(d), Equals(true));

    d.move(XAxis, 0.7f);
            AssertThat(!a.contains(d), Equals(true));

    a.move(XAxis, 0.3f);
            AssertThat(a.contains(d), Equals(true));
        });

        it("splits", [&](){
            AABB a(glm::vec3(2, 3, 5), glm::vec3(12, 100, 25));
            AABB b, c;
            AABB d, e;

            for(int _axis = 0; _axis < 3; _axis++) {
                Axis axis = (Axis)_axis;

                a.split(b, c, axis);

                AssertThat(a.contains(b) && a.contains(c), Equals(true));

                AssertThat(b.extent(XAxis), Equals(c.extent(XAxis)));
                AssertThat(b.extent(YAxis), Equals(c.extent(YAxis)));
                AssertThat(b.extent(ZAxis), Equals(c.extent(ZAxis)));

                AssertThat(b.extent(axis) + c.extent(axis) , EqualsWithDelta(a.extent(axis), 0.1f));
                AssertThat(b.axisMin(axis) + b.extent(axis) , EqualsWithDelta(c.axisMin(axis), 0.1f));
            }

        });

        it("recusriveSplits", [&]() {
            AABB a(glm::vec3(2, 3, 5), glm::vec3(10, 67, 37));

            std::list<AABB> splitted = a.recursiveSplit(2, XAxis);

            AssertThat(splitted.size(), Equals(8));

            std::vector<AABB> splittedv(splitted.begin(), splitted.end());

            for(int b = 0; b < 8; b++) {
                AssertThat(splittedv[b].extent(XAxis), Equals(4));
                AssertThat(splittedv[b].extent(YAxis), Equals(32));
                AssertThat(splittedv[b].extent(ZAxis), Equals(16));
            }
        });
    });
});

int main(int argc, char* argv[]) {
  return bandit::run(argc, argv);
}


