#pragma once

#include "glow\ref_ptr.h"
#include "glow\Texture.h"
#include "glow\Program.h"
#include "glow\VertexArrayObject.h"
#include "glow\Buffer.h"

class Game {

public:
	void initialization();
	void update(float delta_sec);
	void draw();
	void resizeEvent(const unsigned int width, const unsigned int height);

private:
	void createAndSetupTexture();
	void createAndSetupShaders();
	void createAndSetupGeometry();

private:
	glow::ref_ptr<glow::Texture> m_texture;

	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;

	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};