#pragma once

#include <list>
#include <memory>

#include <glm/glm.hpp>

namespace glow {
    class Buffer;
    class VertexArrayObject;
    class Program;
}

class AABB;
class Camera;
class CubeMesh;
class WorldTreeNode;

/**
    Able to render a set of AABBs, as wireframes only, currently
*/
class AABBRenderer {
public:
    AABBRenderer();

    void clear();

    void addAABB(const AABB& aabb);

    void draw(const Camera& camera);


protected:
    bool m_initialized;

    glow::ref_ptr<glow::Program> m_program;

    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    glow::ref_ptr<glow::Buffer> m_aabbBuffer;
    glow::ref_ptr<glow::Buffer> m_wireframeBuffer;

    std::unique_ptr<CubeMesh> m_cubeMesh;

    std::vector<std::pair<glm::vec3, glm::vec3>> m_aabbs;

    void intialize();
};

