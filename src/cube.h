#pragma once
#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>


class Cube {
public:
    Cube();

	const glm::vec4 center();
	virtual void draw();
	virtual void drawtest(glm::mat4 projection);
    virtual void update(float delta_sec);
  
private:
    void createAndSetupShaders();
    void createAndSetupGeometry();

	glm::mat4 m_model_matrix;

	glow::ref_ptr<glow::Texture> m_texture;
	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};