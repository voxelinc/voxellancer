#pragma once

#include "utils/aabbrenderer.h"


class WorldTree;

class WorldTreeRenderer {
public:
    WorldTreeRenderer();
    ~WorldTreeRenderer();

    void draw(const Camera& camera, const WorldTree& tree);


protected:
    std::unique_ptr<AABBRenderer> m_renderer;

    void poll(WorldTreeNode* node);
};

