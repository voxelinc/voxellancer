#pragma once

#include "utils/aabbrenderer.h"



class WorldTreeRenderer {
public:
    WorldTreeRenderer();
    ~WorldTreeRenderer();

    void draw(const Camera& camera);


protected:
    bool m_initialized;
    std::unique_ptr<AABBRenderer> m_renderer;

    void initialize();
    void poll(WorldTreeNode* node);
};

