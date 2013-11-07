#define BOOST_TEST_MODULE test_worldtreenode

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include "worldtree/worldtreenode.h"

BOOST_AUTO_TEST_SUITE(test_worldtreenode)

BOOST_AUTO_TEST_CASE(simpleInsert) {
    WorldtreeNode *node = new WorldtreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
    WorldtreeGeode *a = new WorldtreeGeode();
    WorldtreeGeode *b = new WorldtreeGeode();
    WorldtreeGeode *c = new WorldtreeGeode();

    a->setAABB(AABB(glm::vec3(0, 0, 0), glm::vec3(5, 5, 5)));
    b->setAABB(AABB(glm::vec3(1, 0, 0), glm::vec3(1.5, 1, 1)));
    c->setAABB(AABB(glm::vec3(-3, -2, -1), glm::vec3(1, 2, 3)));

    node->insert(b);
    BOOST_CHECK_EQUAL(node->geodes().size(), 1);
    BOOST_CHECK_EQUAL(node->subnodes().size(), 0);
    BOOST_CHECK_EQUAL(b->containingNode(), node);

    float oldWidth = node->aabb().extent(XAxis);

    node->insert(a);
    BOOST_CHECK_EQUAL(node->geodes().size(), 0);
    BOOST_CHECK_EQUAL(node->subnodes().size(), 8);
    BOOST_CHECK_CLOSE(node->aabb().extent(XAxis), oldWidth*2, 5);
    BOOST_CHECK_EQUAL(a->containingNode(), node);

    node->insert(c);
    BOOST_CHECK_EQUAL(node->geodes().size(), 0);
    BOOST_CHECK_EQUAL(node->subnodes().size(), 8);
    BOOST_CHECK_EQUAL(c->containingNode(), node);
    BOOST_CHECK_CLOSE(node->aabb().extent(XAxis), oldWidth*4, 5);

    delete a, b, c;
}

BOOST_AUTO_TEST_CASE(inAABB) {
    WorldtreeNode *node = new WorldtreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
    WorldtreeGeode *e1, *e2;
    WorldtreeGeode *a, *b, *c;

    e1 = new WorldtreeGeode();
    e2 = new WorldtreeGeode();

    e1->setAABB(AABB(glm::vec3(-100, -100, -100), glm::vec3(-99, -99, -99)));
    e2->setAABB(AABB(glm::vec3(99, 99, 99), glm::vec3(100, 100, 100)));

    node->insert(e1);
    node->insert(e2);

    a = new WorldtreeGeode();
    b = new WorldtreeGeode();
    c = new WorldtreeGeode();

    a->setAABB(AABB(glm::vec3(50, 20, 30), glm::vec3(60, 30, 35)));
    b->setAABB(AABB(glm::vec3(5, 20, 30), glm::vec3(15, 30, 35)));
    c->setAABB(AABB(glm::vec3(-50, 0, 0), glm::vec3(0, 5, 5)));

    node->insert(a);
    node->insert(b);
    node->insert(c);

    std::set<WorldtreeGeode*> q1 = node->geodesInAABB(AABB(glm::vec3(-100, -100, -100), glm::vec3(100, 100, 100)));
    BOOST_CHECK_EQUAL(q1.size(), 5);

    std::set<WorldtreeGeode*> q2 = node->geodesInAABB(AABB(glm::vec3(-98, -98, -98), glm::vec3(100, 100, 100)));
    BOOST_CHECK_EQUAL(q2.size(), 4);

    std::set<WorldtreeGeode*> q3 = node->geodesInAABB(AABB(glm::vec3(-45, 2, 4), glm::vec3(55, 25, 40)));
    BOOST_CHECK_EQUAL(q3.size(), 3);

    delete e1, e2, a, b, c;
}


BOOST_AUTO_TEST_CASE(movement) {
    WorldtreeNode *node = new WorldtreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
    WorldtreeGeode *e1, *e2;
    WorldtreeGeode *a;

    e1 = new WorldtreeGeode();
    e2 = new WorldtreeGeode();

    e1->setAABB(AABB(glm::vec3(-100, -100, -100), glm::vec3(-99, -99, -99)));
    e2->setAABB(AABB(glm::vec3(99, 99, 99), glm::vec3(100, 100, 100)));

    node->insert(e1);
    node->insert(e2);

    a = new WorldtreeGeode();
    a->setAABB(AABB(glm::vec3(50, 20, 30), glm::vec3(60, 30, 35)));
    node->insert(a);

    std::set<WorldtreeGeode*> q1 = node->geodesInAABB(AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36)));
    BOOST_CHECK_EQUAL(q1.size(), 1);
    BOOST_CHECK(q1.find(a) != q1.end());

    a->setAABB(AABB(glm::vec3(-10, 40, 30), glm::vec3(0, 50, 35)));
    node->aabbChanged(a);

    std::set<WorldtreeGeode*> q2 = node->geodesInAABB(AABB(glm::vec3(-9, 41, 31), glm::vec3(-8, 42, 32)));
    BOOST_CHECK_EQUAL(q2.size(), 1);
    BOOST_CHECK(q2.find(a) != q2.end());

    std::set<WorldtreeGeode*> q3 = node->geodesInAABB(AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36)));
    BOOST_CHECK_EQUAL(q3.size(), 0);
    BOOST_CHECK(q3.find(a) == q3.end());

    delete e1, e2, a;
}

BOOST_AUTO_TEST_SUITE_END()
