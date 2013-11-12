#include <bandit/bandit.h>

#include "clusterloader.h"

using namespace bandit;

go_bandit([]() {
	describe("ClusterLoader", []() {
		it("loads simple basicship", [&]() {

			Voxelcluster *vcsv = new Voxelcluster();
			Voxelcluster *vzox = new Voxelcluster();
			ClusterLoader *l = new ClusterLoader();
			l->loadClusterFromFile("data/voxelcluster/loadertest.csv", vcsv);
			l->loadClusterFromFile("data/voxelcluster/loadertest.zox", vzox);
			AssertThat(vcsv->voxelCount(), Equals(1));
			AssertThat(vzox->voxelCount(), Equals(1));

			vcsv->removeVoxel(cvec3(0, 0, 0));
			vzox->removeVoxel(cvec3(0, 0, 0));
			AssertThat(vcsv->voxelCount(), Equals(0));
			AssertThat(vzox->voxelCount(), Equals(0));
		});
	});
});



#ifndef TEST_ALL
int main(int argc, char *argv[]) {
	return bandit::run(argc, argv);
}
#endif
