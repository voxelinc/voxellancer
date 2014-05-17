#include <bandit/bandit.h>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include "../bandit_extension/vec3helper.h"
#include "voxel/voxelcluster.h"
#include "voxel/voxel.h"
#include "voxel/voxelrenderdata.h"

using namespace bandit;


go_bandit([](){
    describe("Voxelcluster", [](){
        VoxelCluster *cluster;

        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        before_each([&](){
            cluster = new VoxelCluster(1.0f);
        });

        after_each([&](){
            delete cluster;
        });

        it("can add/remove voxel", [&]() {
            cluster->addVoxel(new Voxel(glm::ivec3(1, 2, 3), 0xFF8000FF));
            AssertThat(cluster->voxel(glm::ivec3(1, 2, 3)) != nullptr, Equals(true));

            cluster->removeVoxel(cluster->voxel(glm::ivec3(1, 2, 3)));
            AssertThat(cluster->voxel(glm::ivec3(1, 2, 3)) == nullptr, Equals(true));
        });
    });
    describe("voxel hasher", []() {
        it("can hash glm::ivec3", [&]() {
            std::hash<glm::ivec3> hash;
            AssertThat(hash(glm::ivec3(0, 0, 0)), Equals(0));
            AssertThat(hash(glm::ivec3(1, 0, 0)), Equals(1*31));
            AssertThat(hash(glm::ivec3(0, 1, 0)), Equals(256 * 31));
            AssertThat(hash(glm::ivec3(0, 0, 1)), Equals((1 << 16) * 31));
            AssertThat(hash(glm::ivec3(127, 1, 1)), Equals(((1 << 16) + 256 + 127) * 31));
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

