#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <glow/ref_ptr.h>

#include "etc/contextdependant.h"

#include "geometry/aabb.h"


namespace glow {
    class Buffer;
    class VertexArrayObject;
    class Program;
}

class Camera;
class CubeMesh;
class WorldTreeNode;

/**
 * Data for the shader
 */
struct AABBData {
    glm::vec3 middle;
    glm::vec3 extent;
};

/**
 * Able to render a set of AABBs.
 * As wireframes only, currently
 */
class AABBRenderer : public ContextDependant {
public:
    AABBRenderer();
    ~AABBRenderer();

    void clear();

    void add(const AABB& aabb);

    void draw(const Camera& camera);


protected:
    bool m_initialized;

    glow::ref_ptr<glow::Program> m_program;

    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    glow::ref_ptr<glow::Buffer> m_aabbBuffer;

    std::unique_ptr<CubeMesh> m_cubeMesh;

    std::vector<AABBData> m_aabbs;


    void initialize();

    void initializeProgram();
    void initializeVAO();

    void beforeContextDestroy();
    void afterContextRebuild();
};

