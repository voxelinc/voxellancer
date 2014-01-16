#include <bandit/bandit.h>

#include <iostream>
#include <list>

#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "world/handler/splitdetector.h"
#include "world/handler/splitter.h"
#include "property/propertymanager.h"
#include "world/helper/splitdata.h"
#include "voxel/voxel.h"

using namespace bandit;

go_bandit([]() {
    describe("Splitdetector and Splitter", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        WorldObject* w = nullptr;
        SplitDetector detector;
        Splitter splitter;

        Voxel* voxels[9];

        before_each([&]() {
            if (w != nullptr)
                delete w;
            w = new WorldObject();
            w->addVoxel(voxels[0] = new Voxel(glm::ivec3(2, 0, 0)));
            w->addVoxel(voxels[1] = new Voxel(glm::ivec3(2, 1, 0)));
            w->addVoxel(voxels[2] = new Voxel(glm::ivec3(2, 2, 0)));
            w->addVoxel(voxels[3] = new Voxel(glm::ivec3(2, 3, 0)));
            w->addVoxel(voxels[4] = new Voxel(glm::ivec3(1, 3, 0)));
            w->addVoxel(voxels[5] = new Voxel(glm::ivec3(0, 3, 0)));
            w->addVoxel(voxels[6] = new Voxel(glm::ivec3(3, 3, 0)));
            w->addVoxel(voxels[7] = new Voxel(glm::ivec3(4, 3, 0)));
            w->addVoxel(voxels[8] = new Voxel(glm::ivec3(5, 3, 0)));
            w->setCrucialVoxel(glm::ivec3(2, 1, 0));

            /*
             y
             3|5 4 3 6 7 8
             2|    2
             1|   (1)
             0|    0
              --------------
               0 1 2 3 4 5 x
            */

        });

        it("detects no split correctly", [&]() {
            WorldObjectModification modification(w);


            modification.removedVoxel(voxels[0]->gridCell());
            w->removeVoxel(voxels[0]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            AssertThat(detector.splitDataList(), IsEmpty());
        });


        it("detects one split correctly", [&]() {
            WorldObjectModification modification(w);


            modification.removedVoxel(voxels[2]->gridCell());
            w->removeVoxel(voxels[2]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            AssertThat(detector.splitDataList().size(), Equals(1));


            // check if the split is the upper part of the voxel without the crucial voxel
            SplitData* splitOff = detector.splitDataList().front();

            AssertThat(splitOff->splitOffVoxels().size(), Equals(6));


            Voxel* oneSplittOffVoxel = splitOff->splitOffVoxels().front();
            AssertThat(oneSplittOffVoxel->gridCell().y, IsGreaterThan(2));
        });


        it("works with destroyed crucial voxels", [&]() {
            WorldObjectModification modification(w);


            modification.removedVoxel(voxels[1]->gridCell());
            w->removeVoxel(voxels[1]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            AssertThat(detector.splitDataList().size(), Equals(1));
        });


        it("detection works with diagonals", [&]() {
            WorldObjectModification modification(w);

            modification.removedVoxel(voxels[3]->gridCell());
            w->removeVoxel(voxels[3]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            AssertThat(detector.splitDataList().size(), Equals(0));
        });


        it("detection works with multiple removed voxels", [&]() {
            WorldObjectModification modification(w);


            modification.removedVoxel(voxels[3]->gridCell());
            w->removeVoxel(voxels[3]);
            modification.removedVoxel(voxels[2]->gridCell());
            w->removeVoxel(voxels[2]);
            modification.removedVoxel(voxels[1]->gridCell());
            w->removeVoxel(voxels[1]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            AssertThat(detector.splitDataList().size(), Equals(2));
        });

        it("splits no split correctly", [&]() {
            WorldObjectModification modification(w);

            w->addVoxel(new Voxel(glm::ivec3(3, 0, 0)));
            w->addVoxel(new Voxel(glm::ivec3(3, 1, 0)));
            modification.removedVoxel(voxels[0]->gridCell());
            w->removeVoxel(voxels[0]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            splitter.split(detector.splitDataList());

            AssertThat(splitter.splitOffWorldObjects().size(), Equals(0));
        });


        it("splits one split correctly", [&]() {
            WorldObjectModification modification(w);

            modification.removedVoxel(voxels[2]->gridCell());
            w->removeVoxel(voxels[2]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);
            splitter.split(detector.splitDataList());

            AssertThat(splitter.splitOffWorldObjects().size(), Equals(1));

            WorldObject* splitOff = splitter.splitOffWorldObjects().front();
            AssertThat(splitOff->voxel(glm::ivec3(2, 3, 0)) == nullptr, IsFalse());
            AssertThat(splitOff->voxel(glm::ivec3(2, 0, 0)) == nullptr, IsTrue());

            AssertThat(w->voxel(glm::ivec3(2, 3, 0)) == nullptr, IsTrue());
            AssertThat(w->voxel(glm::ivec3(2, 0, 0)) == nullptr, IsFalse());

        });


        it("splitting works with multiple splittoffs", [&]() {
            WorldObjectModification modification(w);

            modification.removedVoxel(voxels[2]->gridCell());
            w->removeVoxel(voxels[2]);
            modification.removedVoxel(voxels[3]->gridCell());
            w->removeVoxel(voxels[3]);

            std::list<WorldObjectModification>l{ modification };
            detector.searchSplitOffs(l);

            splitter.split(detector.splitDataList());

            AssertThat(splitter.splitOffWorldObjects().size(), Equals(2));
        });


    });
});
