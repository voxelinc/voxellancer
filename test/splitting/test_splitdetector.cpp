#include <bandit/bandit.h>

#include <iostream>
#include <list>

#include "../bandit_extension/vec3helper.h"
#include "worldobject/worldobject.h"
#include "world/handler/splitdetector.h"
#include "world/handler/splitter.h"
#include "property/propertymanager.h"
#include "world/helper/worldobjectsplit.h"
#include "voxel/voxel.h"

using namespace bandit;

go_bandit([]() {
    describe("Splitdetector", []() {
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");

        WorldObject* w = nullptr;
        SplitDetector detector;

        Voxel* voxels[9];

        before_each([&]() {
            if (w != nullptr)
                delete w;
            w = new WorldObject();
            w->addVoxel(voxel[0] = new Voxel(glm::ivec3(2, 0, 0))); // 1
            w->addVoxel(voxel[1] = new Voxel(glm::ivec3(2, 1, 0))); // 2
            w->addVoxel(voxel[2] = new Voxel(glm::ivec3(2, 2, 0))); // 3
            w->addVoxel(voxel[3] = new Voxel(glm::ivec3(2, 3, 0))); // 4
            w->addVoxel(voxel[4] = new Voxel(glm::ivec3(1, 3, 0))); // 5
            w->addVoxel(voxel[5] = new Voxel(glm::ivec3(0, 3, 0))); // 6
            w->addVoxel(voxel[6] = new Voxel(glm::ivec3(3, 3, 0))); // 7
            w->addVoxel(voxel[7] = new Voxel(glm::ivec3(4, 3, 0))); // 8
            w->addVoxel(voxel[8] = new Voxel(glm::ivec3(5, 3, 0))); // 9
            w->setCrucialVoxel(glm::ivec3(2, 1, 0));

            /*
             y
             3|6 5 4 7 8 9
             2|    3
             1|   (2)
             0|    1
              --------------
               0 1 2 3 4 5 x
            */

        });

        it("detects no split correctly", [&]() {
            WorldObjectModification modification(w);

            w->removeVoxel(voxel[0]);
            modification.removedVoxel(voxel[0]->gridCell());

            detector.searchSplitOffs(std::list<WorldObjectModification>{ modification });

            AssertThat(detector.worldObjectSplits(), IsEmpty());
        });


        it("detects one split correctly", [&]() {
            WorldObjectModification modification(w);

            w->removeVoxel(voxel[2]);
            modification.removedVoxel(voxel[2]->gridCell());

            detector.searchSplitOffs(std::list<WorldObjectModification>{ modification });

            AssertThat(detector.worldObjectSplits().size(), Equals(1));

            // check if the split is the upper part of the voxel without the crucial voxel
            WorldObjectSplit* splitOff = detector.worldObjectSplits().front();
            AssertThat(splitOff->splitOffVoxels().size(), Equals(6));


            Voxel* oneSplittOffVoxel = splitOff->splitOffVoxels().front();
            AssertThat(oneSplittOffVoxel->gridCell().y, IsGreaterThan(2));
        });


        it("works with destroyed crucial voxel", [&]() {
            WorldObjectModification modification(w);

            w->removeVoxel(voxel[1]);
            modification.removedVoxel(voxel[1]->gridCell());

            detector.searchSplitOffs(std::list<WorldObjectModification>{ modification });

            AssertThat(detector.worldObjectSplits().size(), Equals(1));
        });


        it("works with multiple splittoffs", [&]() {
            WorldObjectModification modification(w);

            w->removeVoxel(voxel[3]);
            modification.removedVoxel(voxel[3]->gridCell());

            detector.searchSplitOffs(std::list<WorldObjectModification>{ modification });

            AssertThat(detector.worldObjectSplits().size(), Equals(2));
        });


        it("works with multiple removed voxels", [&]() {
            WorldObjectModification modification(w);

            w->removeVoxel(voxel[3]);
            modification.removedVoxel(voxel[3]->gridCell());
            w->removeVoxel(voxel[2]);
            modification.removedVoxel(voxel[2]->gridCell());
            w->removeVoxel(voxel[1]);
            modification.removedVoxel(voxel[1]->gridCell());

            detector.searchSplitOffs(std::list<WorldObjectModification>{ modification });

            AssertThat(detector.worldObjectSplits().size(), Equals(2));
        });

    });
});
