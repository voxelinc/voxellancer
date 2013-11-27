#include <bandit/bandit.h>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "../bandit_extension/vec3helper.h"
#include "voxel/voxelcluster.h"

using namespace bandit;


go_bandit([](){
    describe("Voxelcluster", [](){
        VoxelCluster *cluster;

        before_each([&](){
            cluster = new VoxelCluster;
        });

        after_each([&](){
            delete cluster;
        });

        it("can add/remove voxel", [&]() {
            cluster->addVoxel(new Voxel(cvec3(1, 2, 3), cvec3(255, 128, 0)));
            AssertThat(cluster->voxel().size(), Equals(1));

            cluster->removeVoxel(cvec3(1, 2, 3));
            AssertThat(cluster->voxel().size(), Equals(0));
        });

        it("test generate texture", [&]() {
            cluster->addVoxel(new Voxel(cvec3('a', 'b', 'c'), cvec3(255, 128, 0)));
            cluster->addVoxel(new Voxel(cvec3(3, 4, 5), cvec3(128, 128, 0)));
            cluster->addVoxel(new Voxel(cvec3(1, 5, 3), cvec3(255, 128, 0)));

            GLuint id1 = cluster->voxelRenderData()->positionTexture()->id();
            GLuint id2 = cluster->voxelRenderData()->colorTexture()->id();

            // cant assert anything usefull just verify that nothing crashes ;)
            AssertThat(cluster->voxelRenderData()->voxelCount(), Equals(3));
        });
    });
    describe("voxel hasher", []() {
        it("can hash cvec3", [&]() {
            VoxelHash hash;
            AssertThat(hash(cvec3(0, 0, 0)), Equals(0));
            AssertThat(hash(cvec3(1, 0, 0)), Equals(1));
            AssertThat(hash(cvec3(0, 1, 0)), Equals(256));
            AssertThat(hash(cvec3(0, 0, 1)), Equals(1 << 16));
            AssertThat(hash(cvec3(127, 1, 1)), Equals((1 << 16) + 256 + 127));
            AssertThat(hash(cvec3(1, 0, 0)), Equals(hash(cvec3(1, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(2, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(-1, 0, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, 1, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, -1, 0))));
            AssertThat(hash(cvec3(1, 0, 0)), !Equals(hash(cvec3(0, 0, 1))));
            AssertThat(hash(cvec3(0, 1, 0)), !Equals(hash(cvec3(0, 0, 1))));

        });
    });
});

