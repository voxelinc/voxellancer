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

        WorldObject *dummy;
        WorldTree *worldTree;

        before_each([&] {
            dummy = new WorldObject();
            worldTree = new WorldTree();
        });

        after_each([&] {
            delete dummy;
            delete worldTree;
        });

        it("simple inserts", [&]() {
            WorldTreeGeode *a = new WorldTreeGeode(dummy);
            WorldTreeGeode *b = new WorldTreeGeode(dummy);
            WorldTreeGeode *c = new WorldTreeGeode(dummy);
            WorldTreeGeode *d = new WorldTreeGeode(dummy);

            a->setAABB(IAABB(glm::ivec3(0, 0, 0), glm::ivec3(5, 5, 5)));
            b->setAABB(IAABB(glm::ivec3(1, 0, 0), glm::ivec3(1.5, 1, 1)));
            c->setAABB(IAABB(glm::ivec3(9, 2, 2), glm::ivec3(10, 3, 3)));
            d->setAABB(IAABB(glm::ivec3(9, 2, 2), glm::ivec3(1000, 3, 3)));

            worldTree->insert(b);
            AssertThat(worldTree->root()->geodes().size(), Equals(1));
            AssertThat(worldTree->root()->subnodes().size(), Equals(0));
            AssertThat(b->containingNode(), Equals(worldTree->root()));

            worldTree->insert(a);
            AssertThat(worldTree->root()->geodes().size(), Equals(2));
            AssertThat(worldTree->root()->subnodes().size(), Equals(0));

            int oldWidth = worldTree->root()->aabb().extent(XAxis);

            worldTree->insert(c);
            AssertThat(worldTree->root()->geodes().size(), Equals(0));
            AssertThat(worldTree->root()->subnodes().size(), Equals(2));
            AssertThat(worldTree->root()->aabb().extent(XAxis), EqualsWithDelta(oldWidth*2, 0.5f));

            worldTree->insert(d);
            AssertThat(worldTree->root()->geodes().size(), Equals(0));
            AssertThat(worldTree->root()->subnodes().size(), Equals(2));
        });

        it("can detect geodes in an AABB", [&]() {
            WorldTreeGeode *e1, *e2;
            WorldTreeGeode *a, *b, *c;
            AABB aabb;

            e1 = new WorldTreeGeode(dummy);
            e2 = new WorldTreeGeode(dummy);

            e1->setAABB(IAABB(glm::ivec3(-100, -100, -100), glm::ivec3(-99, -99, -99)));
            e2->setAABB(IAABB(glm::ivec3(99, 99, 99), glm::ivec3(100, 100, 100)));

            worldTree->insert(e1);
            worldTree->insert(e2);

            a = new WorldTreeGeode(dummy);
            b = new WorldTreeGeode(dummy);
            c = new WorldTreeGeode(dummy);

            a->setAABB(IAABB(glm::ivec3(50, 20, 30), glm::ivec3(60, 30, 35)));
            b->setAABB(IAABB(glm::ivec3(5, 20, 30), glm::ivec3(15, 30, 35)));
            c->setAABB(IAABB(glm::ivec3(-50, 0, 0), glm::ivec3(0, 5, 5)));

            worldTree->insert(a);
            worldTree->insert(b);
            worldTree->insert(c);

            aabb = AABB(glm::vec3(-100, -100, -100), glm::vec3(100, 100, 100));
            std::set<WorldTreeGeode*> q1 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
            AssertThat(q1.size(), Equals(5));

            aabb = AABB(glm::vec3(-98, -98, -98), glm::vec3(100, 100, 100));
            std::set<WorldTreeGeode*> q2 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
            AssertThat(q2.size(), Equals(4));

            aabb = AABB(glm::vec3(-45, 2, 4), glm::vec3(55, 25, 40));
            std::set<WorldTreeGeode*> q3 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
            AssertThat(q3.size(), Equals(3));
        });

        it("moves geodes correctly within the tree on aabb change", [&]() {
            WorldTreeGeode *e1, *e2;
            WorldTreeGeode *a;
            AABB aabb;

            e1 = new WorldTreeGeode(dummy);
            e2 = new WorldTreeGeode(dummy);

            e1->setAABB(IAABB(glm::ivec3(-100, -100, -100), glm::ivec3(-99, -99, -99)));
            e2->setAABB(IAABB(glm::ivec3(99, 99, 99), glm::ivec3(100, 100, 100)));

            worldTree->insert(e1);
            worldTree->insert(e2);

            a = new WorldTreeGeode(dummy);
            a->setAABB(IAABB(glm::ivec3(50, 20, 30), glm::ivec3(60, 30, 35)));
            worldTree->insert(a);

            aabb = AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36));
            std::set<WorldTreeGeode*> q1 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
            AssertThat(q1.size(), Equals(1));
            AssertThat(q1.find(a) != q1.end(), Equals(true));

            a->setAABB(IAABB(glm::ivec3(-10, 40, 30), glm::ivec3(0, 50, 35)));
            worldTree->aabbChanged(a);

            aabb = AABB(glm::vec3(-9, 41, 31), glm::vec3(-8, 42, 32));
            std::set<WorldTreeGeode*> q2 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
            AssertThat(q2.size(), Equals(1));
            AssertThat(q2.find(a) != q2.end(), Equals(true));

            aabb = AABB(glm::vec3(55, 25, 29), glm::vec3(56, 26, 36));
            std::set<WorldTreeGeode*> q3 = WorldTreeQuery(worldTree, &aabb).nearGeodes();
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
            s2.setRadius(1.7f);
            s3.setRadius(3);

            AssertThat(WorldTreeQuery(&worldTree, &s1).intersectingVoxels().size(), Equals(0));
            AssertThat(WorldTreeQuery(&worldTree, &s2).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery(&worldTree, &s3).intersectingVoxels().size(), Equals(3));

            Sphere s4(glm::vec3(1, 1.5, 0), 1.5);
            AssertThat(WorldTreeQuery(&worldTree, &s4).intersectingVoxels().size(), Equals(2));
        });

        it("can be queried for voxels in ray", [&]() {
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            a.setPosition(glm::vec3(1.5, 1.5, 0));
            worldTree->insert(&a);

            Ray r1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
            Ray r2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 1.0f, 0.0f));

            AssertThat(WorldTreeQuery(worldTree, &r1).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery(worldTree, &r1).areVoxelsIntersecting(), Equals(true));
            AssertThat(WorldTreeQuery(worldTree, &r1).intersectingWorldObjects().size(), Equals(1));
            AssertThat(WorldTreeQuery(worldTree, &r2).intersectingVoxels().size(), Equals(0));
            AssertThat(WorldTreeQuery(worldTree, &r2).areVoxelsIntersecting(), Equals(false));
            AssertThat(WorldTreeQuery(worldTree, &r2).intersectingWorldObjects().size(), Equals(0));

            WorldObject b;

            b.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            b.addVoxel(new Voxel(glm::ivec3(1,0,0)));
            b.setPosition(glm::vec3(3.0f, 3.0f, 0));
            worldTree->insert(&b);

            Ray r3(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-1.0f, -2.0f, 0.0f));
            AssertThat(WorldTreeQuery(worldTree, &r3).intersectingVoxels().size(), Equals(2));
            AssertThat(WorldTreeQuery(worldTree, &r3).areVoxelsIntersecting(), Equals(true));
            AssertThat(WorldTreeQuery(worldTree, &r3).intersectingWorldObjects().size(), Equals(2));
        });

        it("can be queried for voxels on line", [&]() {
            WorldObject a;

            a.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            a.setPosition(glm::vec3(1.5, 1.5, 0));
            worldTree->insert(&a);

            Line l1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.3f, 1.3f, 0.0f));
            Line l2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 1.0f, 0.0f));

            AssertThat(WorldTreeQuery(worldTree, &l1).intersectingVoxels().size(), Equals(1));
            AssertThat(WorldTreeQuery(worldTree, &l2).intersectingVoxels().size(), Equals(0));

            WorldObject b;

            b.addVoxel(new Voxel(glm::ivec3(0,0,0)));
            b.addVoxel(new Voxel(glm::ivec3(1,0,0)));
            b.setPosition(glm::vec3(3.0f, 3.0f, 0));
            worldTree->insert(&b);

            Line l3(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-1.0f, -2.0f, 0.0f));
            AssertThat(WorldTreeQuery(worldTree, &l3).intersectingVoxels().size(), Equals(1));

            Line l4(glm::vec3(3.0f, 5.0f, 0.0f), glm::vec3(-10.0f, -20.0f, 0.0f));
            AssertThat(WorldTreeQuery(worldTree, &l4).intersectingVoxels().size(), Equals(2));
            AssertThat(WorldTreeQuery(worldTree, &l4).intersectingWorldObjects().size(), Equals(2));
        });
    });
});



