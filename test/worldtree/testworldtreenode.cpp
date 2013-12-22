#include <bandit/bandit.h>

#include <iostream>

#include "../bandit_extension/vec3helper.h"
#include "worldtree/worldtree.h"
#include "worldtree/worldtreenode.h"
#include "worldtree/worldtreequery.h"
#include "worldobject/worldobject.h"
#include "geometry/line.h"


using namespace bandit;

go_bandit([]() {
    describe("WorldTree", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        WorldObject *dummy = new WorldObject();

        it("simpleInserts", [&]() {
            WorldTreeNode *node = new WorldTreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
            WorldTreeGeode *a = new WorldTreeGeode(); a->setWorldObject(dummy);
            WorldTreeGeode *b = new WorldTreeGeode(); b->setWorldObject(dummy);
            WorldTreeGeode *c = new WorldTreeGeode(); c->setWorldObject(dummy);

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
            WorldTreeNode *node = new WorldTreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
            WorldTreeGeode *e1, *e2;
            WorldTreeGeode *a, *b, *c;

            e1 = new WorldTreeGeode(); e1->setWorldObject(dummy);
            e2 = new WorldTreeGeode(); e2->setWorldObject(dummy);

            e1->setAABB(AABB(glm::vec3(-100, -100, -100), glm::vec3(-99, -99, -99)));
            e2->setAABB(AABB(glm::vec3(99, 99, 99), glm::vec3(100, 100, 100)));

            node->insert(e1);
            node->insert(e2);

            a = new WorldTreeGeode(); a->setWorldObject(dummy);
            b = new WorldTreeGeode(); b->setWorldObject(dummy);
            c = new WorldTreeGeode(); c->setWorldObject(dummy);

            a->setAABB(AABB(glm::vec3(50, 20, 30), glm::vec3(60, 30, 35)));
            b->setAABB(AABB(glm::vec3(5, 20, 30), glm::vec3(15, 30, 35)));
            c->setAABB(AABB(glm::vec3(-50, 0, 0), glm::vec3(0, 5, 5)));

            node->insert(a);
            node->insert(b);
            node->insert(c);

            std::set<WorldTreeGeode*> q1 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(-100, -100, -100), glm::vec3(100, 100, 100))).nearGeodes();
            AssertThat(q1.size(), Equals(5));

            std::set<WorldTreeGeode*> q2 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(-98, -98, -98), glm::vec3(100, 100, 100))).nearGeodes();
            AssertThat(q2.size(), Equals(4));

            std::set<WorldTreeGeode*> q3 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(-45, 2, 4), glm::vec3(55, 25, 40))).nearGeodes();
            AssertThat(q3.size(), Equals(3));

            delete e1, e2, a, b, c;
        });

        it("moves geodes correctly within the tree on aabb change", [&]() {
            WorldTreeNode *node = new WorldTreeNode(0, nullptr, AABB(glm::vec3(-2, -2, -2), glm::vec3(2, 2, 2)));
            WorldTreeGeode *e1, *e2;
            WorldTreeGeode *a;

            e1 = new WorldTreeGeode();e1->setWorldObject(dummy);
            e2 = new WorldTreeGeode();e2->setWorldObject(dummy);

            e1->setAABB(AABB(glm::vec3(-100, -100, -100), glm::vec3(-99, -99, -99)));
            e2->setAABB(AABB(glm::vec3(99, 99, 99), glm::vec3(100, 100, 100)));

            node->insert(e1);
            node->insert(e2);

            a = new WorldTreeGeode(); a->setWorldObject(dummy);
            a->setAABB(AABB(glm::vec3(50, 20, 30), glm::vec3(60, 30, 35)));
            node->insert(a);

            std::set<WorldTreeGeode*> q1 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36))).nearGeodes();
            AssertThat(q1.size(), Equals(1));
            AssertThat(q1.find(a) != q1.end(), Equals(true));

            a->setAABB(AABB(glm::vec3(-10, 40, 30), glm::vec3(0, 50, 35)));
            node->aabbChanged(a);

            std::set<WorldTreeGeode*> q2 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(-9, 41, 31), glm::vec3(-8, 42, 32))).nearGeodes();
            AssertThat(q2.size(), Equals(1));
            AssertThat(q2.find(a) != q2.end(), Equals(true));

            std::set<WorldTreeGeode*> q3 = WorldTreeQuery<AABB>(node, AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36))).nearGeodes();
            AssertThat(q3.size(), Equals(0));
            AssertThat(q3.find(a) == q3.end(), Equals(true));

            delete e1, e2, a;
        });

        it("can be queried for voxels in sphere", [&]() {
            WorldTree worldTree;
            WorldObject a;
            WorldObject b;

            a.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            a.addVoxel(new Voxel(glm::ivec3(1,0,0)));
            a.setPosition(glm::vec3(2.5, 0, 0));
            worldTree.insert(&a);

            b.setPosition(glm::vec3(0,3,0));
            b.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            worldTree.insert(&b);

            Sphere s1, s2, s3;

            s1.setRadius(1);
            s2.setRadius(1.7);
            s3.setRadius(3);

            AssertThat(WorldTreeQuery<Sphere>(&worldTree, s1).intersectingVoxels().size(), Equals(0));
            AssertThat(WorldTreeQuery<Sphere>(&worldTree, s2).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery<Sphere>(&worldTree, s3).intersectingVoxels().size(), Equals(3));

            Sphere s4(glm::vec3(1, 1.5, 0), 1.5);
            AssertThat(WorldTreeQuery<Sphere>(&worldTree, s4).intersectingVoxels().size(), Equals(2));
        });

        it("can be queried for voxels in ray", [&]() {
            WorldTree worldTree;
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            a.setPosition(glm::vec3(1.5, 1.5, 0));
            worldTree.insert(&a);

            Ray r1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            Ray r2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 1.0f, 0.0f));

            AssertThat(WorldTreeQuery<Ray>(&worldTree, r1).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery<Ray>(&worldTree, r1).areVoxelsIntersecting(), Equals(true));
            AssertThat(WorldTreeQuery<Ray>(&worldTree, r2).intersectingVoxels().size(), Equals(0));
            AssertThat(WorldTreeQuery<Ray>(&worldTree, r2).areVoxelsIntersecting(), Equals(false));

            WorldObject b;

            b.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            b.addVoxel(new Voxel(glm::ivec3(1,0,0)));
            b.setPosition(glm::vec3(3.0f, 3.0f, 0));
            worldTree.insert(&b);

            Ray r3(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-1.0f, -2.0f, 0.0f));
            AssertThat(WorldTreeQuery<Ray>(&worldTree, r3).intersectingVoxels().size(), Equals(2));
            AssertThat(WorldTreeQuery<Ray>(&worldTree, r1).areVoxelsIntersecting(), Equals(true));
        });

        it("can be queried for voxels on line", [&]() {
            WorldTree worldTree;
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            a.setPosition(glm::vec3(1.5, 1.5, 0));
            worldTree.insert(&a);

            Line l1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.3f, 1.3f, 0.0f));
            Line l2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 1.0f, 0.0f));

            AssertThat(WorldTreeQuery<Line>(&worldTree, l1).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery<Line>(&worldTree, l2).intersectingVoxels().size(), Equals(0));

            WorldObject b;

            b.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            b.addVoxel(new Voxel(glm::ivec3(1,0,0)));
            b.setPosition(glm::vec3(3.0f, 3.0f, 0));
            worldTree.insert(&b);

            Line l3(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-1.0f, -2.0f, 0.0f));
            AssertThat(WorldTreeQuery<Line>(&worldTree, l3).intersectingVoxels().size(), Equals(1));

            Line l4(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-10.0f, -20.0f, 0.0f));
            AssertThat(WorldTreeQuery<Line>(&worldTree, l4).intersectingVoxels().size(), Equals(2));
        });
    });
});



