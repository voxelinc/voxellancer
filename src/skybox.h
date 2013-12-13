#pragma once
#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include "camera.h"

class Skybox {
public:
	Skybox();
	virtual ~Skybox();

    void draw(Camera *camera);

    glow::ref_ptr<glow::Texture> m_texture;

protected:

	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};