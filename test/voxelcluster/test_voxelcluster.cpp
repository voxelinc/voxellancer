#include <bandit/bandit.h>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "voxel/voxelcluster.h"

using namespace bandit;


go_bandit([](){
    describe("Voxelcluster", [](){
        before_each([&](){

        });

        it("can add/remove voxel", [&]() {
            Voxelcluster cluster;

            cluster.addVoxel(Voxel(cvec3(1, 2, 3), ucvec3(255, 128, 0)));
            AssertThat(cluster.voxelCount(), Equals(1));

            cluster.removeVoxel(cvec3(1, 2, 3));
            AssertThat(cluster.voxelCount(), Equals(0));
        });
        it("can hash cvec3", [&]() {
            VoxelHash hash;

            AssertThat(hash(cvec3(1, 0, 0)), Equals(hash(cvec3(1, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(2, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(-1, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, 1, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, -1, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, 0, 1))));
            AssertThat(hash(cvec3(0, 1, 0)), !Equals(hash(cvec3(0, 0, 1))));

        });

        it("test generate texture", [&]() {
            Voxelcluster cluster;

            cluster.addVoxel(Voxel(cvec3('a', 'b', 'c'), ucvec3(255, 128, 0)));
            cluster.addVoxel(Voxel(cvec3(3, 4, 5), ucvec3(128, 128, 0)));
            cluster.addVoxel(Voxel(cvec3(1, 5, 3), ucvec3(255, 128, 0)));

            GLuint id1 = cluster.positionTexture()->id();
            GLuint id2 = cluster.colorTexture()->id();

            // cant assert anything usefull just verify that nothing crashes ;)
            AssertThat(cluster.voxelCount(), Equals(3));
        });
    });
});

#ifndef TEST_ALL
int main(int argc, char *argv[]) {
    return bandit::run(argc, argv);
}
#endif
