#pragma once
#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include "voxelcluster.h"

class Camera;

class Cube {
public:
    Cube();

    void prepareDraw(Camera * camera);
    void draw(VoxelCluster * cluster);
    void afterDraw();
  
private:
    void createAndSetupShaders();
    void createAndSetupGeometry();
    glow::ref_ptr<glow::Texture> m_texture;
	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};