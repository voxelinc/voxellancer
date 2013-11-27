#include <bandit/bandit.h>

#include "resource/clusterloader.h"
#include "voxel/voxelcluster.h"

using namespace bandit;

go_bandit([]() {
	describe("ClusterLoader", []() {
		it("loads simple csv", [&]() {

            std::vector<Voxel*> *vcsv = new std::vector<Voxel*>();
			ClusterLoader *l = new ClusterLoader();
			l->load("test/loader/loadertest.csv", vcsv);
            AssertThat(vcsv->size(), Equals(1));

		});
        it("loads simple zox", [&]() {

            std::vector<Voxel*> *vzox = new std::vector<Voxel*>();
            ClusterLoader *l = new ClusterLoader();
            l->load("test/loader/loadertest.zox", vzox);
            AssertThat(vzox->size(), Equals(1));

        });
	});
});


