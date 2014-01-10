#pragma once
#include <glow/ref_ptr.h>


namespace glow {
	class Texture;
	class Program;
	class VertexArrayObject;
	class Buffer;
};

class Camera;
class VoxelCluster;

class VoxelRenderer {
public:
    static VoxelRenderer* instance();

    void prepareDraw(Camera * camera, bool withBorder = true);
    void draw(VoxelCluster * cluster);
    void afterDraw();

    bool prepared();


protected:
    static VoxelRenderer* s_instance;

    glow::ref_ptr<glow::Texture> m_texture;
	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
    bool m_prepared;


    VoxelRenderer();

    void createAndSetupShaders();
    void createAndSetupGeometry();
};
