#define BOOST_TEST_MODULE test_aabb

#include <iostream>
#include <boost/test/included/unit_test.hpp>


#include "geometry/aabb.h"

BOOST_AUTO_TEST_SUITE(test_aabb)

BOOST_AUTO_TEST_CASE(bounds) {
    AABB a(glm::vec3(3, -2, 1), glm::vec3(8, 5, 3));


    BOOST_CHECK_EQUAL(a.extent(XAxis), 5);
    BOOST_CHECK_EQUAL(a.extent(YAxis), 7);
    BOOST_CHECK_EQUAL(a.extent(ZAxis), 2);

    BOOST_CHECK_EQUAL(a.axisMin(XAxis), 3);
    BOOST_CHECK_EQUAL(a.axisMax(XAxis), 8);
    BOOST_CHECK_EQUAL(a.axisMin(ZAxis), 1);
    BOOST_CHECK_EQUAL(a.axisMax(ZAxis), 3);
    BOOST_CHECK_EQUAL(a.axisMax(YAxis), 5);
    BOOST_CHECK_EQUAL(a.axisMin(YAxis), -2);
}

BOOST_AUTO_TEST_CASE(intersection) {
    AABB a(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    AABB b(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    BOOST_CHECK(a.intersects(b) && b.intersects(a));

    a.move(XAxis, 1);
    BOOST_CHECK(!(a.intersects(b) && b.intersects(a)));

    b.move(XAxis, 0.2f);
    BOOST_CHECK(a.intersects(b) && b.intersects(a));

    a.move(glm::vec3(-1.5, -0.8, -0.8));
    b.move(glm::vec3(-0.2, 0, 0));
    BOOST_CHECK(a.intersects(b) && b.intersects(a));
}

BOOST_AUTO_TEST_CASE(containing) {
    AABB a(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    AABB b(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    AABB c(glm::vec3(0, 0, 0), glm::vec3(0.3, 0.4, 1.5));
    AABB d(glm::vec3(0, 0, 0), glm::vec3(0.3, 0.4, 0.5));
    AABB e(glm::vec3(-1, 0.2, 0.2), glm::vec3(0.3, 0.4, 0.5));

    BOOST_CHECK(a.contains(b) && b.contains(a));
    BOOST_CHECK(!a.contains(c));
    BOOST_CHECK(!a.contains(e));
    BOOST_CHECK(a.contains(d));

    a.move(XAxis, 0.1f);
    BOOST_CHECK(!(a.contains(b) && b.contains(a)));

    d.move(glm::vec3(0.2, 0.4, 0.1));
    BOOST_CHECK(a.contains(d));

    d.move(XAxis, 0.7f);
    BOOST_CHECK(!a.contains(d));

    a.move(XAxis, 0.3f);
    BOOST_CHECK(a.contains(d));
}

BOOST_AUTO_TEST_CASE(splitting) {
    AABB a(glm::vec3(2, 3, 5), glm::vec3(12, 100, 25));
    AABB b, c;
    AABB d, e;

    for(int _axis = 0; _axis < 3; _axis++) {
        Axis axis = (Axis)_axis;

        a.split(b, c, axis);

        BOOST_CHECK(a.contains(b) && a.contains(c));

        BOOST_CHECK_EQUAL(b.extent(XAxis), c.extent(XAxis));
        BOOST_CHECK_EQUAL(b.extent(YAxis), c.extent(YAxis));
        BOOST_CHECK_EQUAL(b.extent(ZAxis), c.extent(ZAxis));

        BOOST_CHECK_CLOSE_FRACTION(b.extent(axis) + c.extent(axis) , a.extent(axis), 0.1f);
        BOOST_CHECK_CLOSE_FRACTION(b.axisMin(axis) + b.extent(axis) , c.axisMin(axis), 0.1f);
    }
}

BOOST_AUTO_TEST_CASE(recursiveSplitting) {
    AABB a(glm::vec3(2, 3, 5), glm::vec3(10, 67, 37));

    std::list<AABB> splitted = a.recursiveSplit(2, XAxis);

    BOOST_CHECK_EQUAL(splitted.size(), 8);

    std::vector<AABB> splittedv(splitted.begin(), splitted.end());

    for(int b = 0; b < 8; b++) {
        BOOST_CHECK_EQUAL(splittedv[b].extent(XAxis), 4);
        BOOST_CHECK_EQUAL(splittedv[b].extent(YAxis), 32);
        BOOST_CHECK_EQUAL(splittedv[b].extent(ZAxis), 16);
    }
}

BOOST_AUTO_TEST_SUITE_END()
