#include <bandit/bandit.h>

#include "resource/clusterloader.h"
#include "voxel/voxelcluster.h"

using namespace bandit;

go_bandit([]() {
	describe("ClusterLoader", []() {
		it("loads simple csv basicship", [&]() {

			VoxelCluster *vcsv = new VoxelCluster();
			ClusterLoader *l = new ClusterLoader();
			l->loadClusterFromFile("test/loader/loadertest.csv", vcsv);
            AssertThat(vcsv->voxelMap().size(), Equals(1));

			vcsv->removeVoxel(cvec3(0, 0, 0));
            AssertThat(vcsv->voxelMap().size(), Equals(0));
		});
        it("loads simple zox basicship", [&]() {

            VoxelCluster *vzox = new VoxelCluster();
            ClusterLoader *l = new ClusterLoader();
            l->loadClusterFromFile("test/loader/loadertest.zox", vzox);
            AssertThat(vzox->voxelMap().size(), Equals(1));

            vzox->removeVoxel(cvec3(0, 0, 0));
            AssertThat(vzox->voxelMap().size(), Equals(0));
        });
	});
});


