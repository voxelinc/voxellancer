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
            cluster = new VoxelCluster(1.0f);
        });

        after_each([&](){
            delete cluster;
        });

        it("can add/remove voxel", [&]() {
            cluster->addVoxel(new Voxel(glm::ivec3(1, 2, 3), 0xFF8000));
            AssertThat(cluster->voxel(glm::ivec3(1, 2, 3)) != nullptr, Equals(true));

            cluster->removeVoxel(cluster->voxel(glm::ivec3(1, 2, 3)));
            AssertThat(cluster->voxel(glm::ivec3(1, 2, 3)) == nullptr, Equals(true));
        });

        it("test generate texture", [&]() {
            cluster->addVoxel(new Voxel(glm::ivec3('a', 'b', 'c'), 0xFF8000));
            cluster->addVoxel(new Voxel(glm::ivec3(3, 4, 5), 0x808000));
            cluster->addVoxel(new Voxel(glm::ivec3(1, 5, 3), 0xFF8000));

            GLuint id1 = cluster->voxelRenderData()->voxelTexture()->id();

            // cant assert anything usefull just verify that nothing crashes ;)
            AssertThat(cluster->voxelRenderData()->voxelCount(), Equals(3));
            AssertThat(cluster->voxelRenderData()->textureSize(), Equals(3)); // 3 voxel with position and texture = 6 texel -> 3x3 texture
        });
    });
    describe("voxel hasher", []() {
        it("can hash glm::ivec3", [&]() {
            std::hash<glm::ivec3> hash;
            AssertThat(hash(glm::ivec3(0, 0, 0)), Equals(0));
            AssertThat(hash(glm::ivec3(1, 0, 0)), Equals(1));
            AssertThat(hash(glm::ivec3(0, 1, 0)), Equals(256));
            AssertThat(hash(glm::ivec3(0, 0, 1)), Equals(1 << 16));
            AssertThat(hash(glm::ivec3(127, 1, 1)), Equals((1 << 16) + 256 + 127));
            AssertThat(hash(glm::ivec3(1, 0, 0)), Equals(hash(glm::ivec3(1, 0, 0))));
            AssertThat(hash(glm::ivec3(1, 0, 0)), !Equals(hash(glm::ivec3(2, 0, 0))));
            AssertThat(hash(glm::ivec3(1, 0, 0)), !Equals(hash(glm::ivec3(-1, 0, 0))));
            AssertThat(hash(glm::ivec3(1, 0, 0)), !Equals(hash(glm::ivec3(0, 1, 0))));
            AssertThat(hash(glm::ivec3(1, 0, 0)), !Equals(hash(glm::ivec3(0, -1, 0))));
            AssertThat(hash(glm::ivec3(1, 0, 0)), !Equals(hash(glm::ivec3(0, 0, 1))));
            AssertThat(hash(glm::ivec3(0, 1, 0)), !Equals(hash(glm::ivec3(0, 0, 1))));
        });
    });
});

