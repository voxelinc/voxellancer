#include <bandit/bandit.h>

#include <iostream>

#include "worldtree/worldtreenode.h"

using namespace bandit;

go_bandit([]() {
    describe("Worldtree", []() {
        it("simpleInserts", [&]() {
            WorldtreeNode *node = new WorldtreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
            WorldtreeGeode *a = new WorldtreeGeode();
            WorldtreeGeode *b = new WorldtreeGeode();
            WorldtreeGeode *c = new WorldtreeGeode();

            a->setAABB(AABB(glm::vec3(0, 0, 0), glm::vec3(5, 5, 5)));
            b->setAABB(AABB(glm::vec3(1, 0, 0), glm::vec3(1.5, 1, 1)));
            c->setAABB(AABB(glm::vec3(-3, -2, -1), glm::vec3(1, 2, 3)));

            node->insert(b);
            AssertThat(node->geodes().size(), Equals(1));
            AssertThat(node->subnodes().size(), Equals(0));
            AssertThat(b->containingNode(), Equals(node));

            float oldWidth = node->aabb().extent(XAxis);

            node->insert(a);
            AssertThat(node->geodes().size(), Equals(0));
            AssertThat(node->subnodes().size(), Equals(8));
            AssertThat(node->aabb().extent(XAxis), EqualsWithDelta(oldWidth*2, 0.5f));
            AssertThat(a->containingNode(), Equals(node));

            node->insert(c);
            AssertThat(node->geodes().size(), Equals(0));
            AssertThat(node->subnodes().size(), Equals(8));
            AssertThat(c->containingNode(), Equals(node));
            AssertThat(node->aabb().extent(XAxis), EqualsWithDelta(oldWidth*4, 0.5f));

            delete a, b, c;
        });

        it("can detect geodes in an AABB", [&]() {
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
            AssertThat(q1.size(), Equals(5));

            std::set<WorldtreeGeode*> q2 = node->geodesInAABB(AABB(glm::vec3(-98, -98, -98), glm::vec3(100, 100, 100)));
            AssertThat(q2.size(), Equals(4));

            std::set<WorldtreeGeode*> q3 = node->geodesInAABB(AABB(glm::vec3(-45, 2, 4), glm::vec3(55, 25, 40)));
            AssertThat(q3.size(), Equals(3));

            delete e1, e2, a, b, c;
        });

        it("moves geodes correctly within the tree on aabb change", [&]() {
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
            AssertThat(q1.size(), Equals(1));
            AssertThat(q1.find(a) != q1.end(), Equals(true));

            a->setAABB(AABB(glm::vec3(-10, 40, 30), glm::vec3(0, 50, 35)));
            node->aabbChanged(a);

            std::set<WorldtreeGeode*> q2 = node->geodesInAABB(AABB(glm::vec3(-9, 41, 31), glm::vec3(-8, 42, 32)));
            AssertThat(q2.size(), Equals(1));
            AssertThat(q2.find(a) != q2.end(), Equals(true));

            std::set<WorldtreeGeode*> q3 = node->geodesInAABB(AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36)));
            AssertThat(q3.size(), Equals(0));
            AssertThat(q3.find(a) == q3.end(), Equals(true));

            delete e1, e2, a;
        });
    });
});



