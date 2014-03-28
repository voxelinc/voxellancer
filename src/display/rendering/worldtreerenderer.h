#pragma once

#include <list>

#include <glm/glm.hpp>


namespace glow {
    class Buffer;
    class VertexArrayObject;
    class Program;
}

class Camera;
class WorldTreeNode;

class WorldTreeRenderer {
public:
    WorldTreeRenderer();

    void draw(const Camera& camera);


protected:
    glow::ref_ptr<glow::Program> m_program;
    glow::ref_ptr<glow::Buffer> m_aabbBuffer;
    glow::ref_ptr<glow::Buffer> m_wireframeBuffer;
    glow::ref_ptr<glow::VertexArrayObject> m_vao;
    std::vector<std::pair<glm::vec3, glm::vec3>> m_aabbs;

    void draw(const Camera& camera, WorldTreeNode* node);
};

