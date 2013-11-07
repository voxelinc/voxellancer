#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>

#include "skybox.h"

#include "ddstexture.h"

Skybox::Skybox() :
	m_texture(0),
	m_shaderProgram(0),
	m_vertexArrayObject(0),
	m_vertexBuffer(0)
{
	/* Texture */
	m_texture = new glow::Texture(GL_TEXTURE_CUBE_MAP);
	if(!DdsTexture::loadImageCube(m_texture,
		"data/skybox/nebula_1024_right1.dds",
		"data/skybox/nebula_1024_left2.dds",
		"data/skybox/nebula_1024_top3.dds",
		"data/skybox/nebula_1024_bottom4.dds",
		"data/skybox/nebula_1024_front5.dds",
		"data/skybox/nebula_1024_back6.dds")){
		throw std::runtime_error("Skybox textures not found. Check working directory?");
	}
	m_texture->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	m_texture->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_texture->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_texture->setParameter(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	/* Shaders */
	glow::Shader * vertexShader = glow::Shader::fromFile(GL_VERTEX_SHADER, "data/skybox.vert");
	glow::Shader * fragmentShader = glow::Shader::fromFile(GL_FRAGMENT_SHADER, "data/skybox.frag");

	m_shaderProgram = new glow::Program();
	m_shaderProgram->attach(vertexShader, fragmentShader);
	m_shaderProgram->bindFragDataLocation(0, "fragColor");

	m_shaderProgram->getUniform<GLint>("texture")->set(0);


	/* Geometry */
	auto vertices = glow::Array<glm::vec3>()
		<< glm::vec3(-1, -1, -1)
		<< glm::vec3(1, -1, -1)
		<< glm::vec3(1, 1, -1)
		<< glm::vec3(-1, 1, -1);

	m_vertexArrayObject = new glow::VertexArrayObject();

	m_vertexBuffer = new glow::Buffer(GL_ARRAY_BUFFER);
	m_vertexBuffer->setData(vertices);

	auto binding1 = m_vertexArrayObject->binding(0);
	auto a_vertex = m_shaderProgram->getAttributeLocation("a_vertex");

	binding1->setAttribute(a_vertex);
	binding1->setBuffer(m_vertexBuffer, 0, sizeof(glm::vec3));
	binding1->setFormat(3, GL_FLOAT, GL_FALSE, 0);

	m_vertexArrayObject->enable(a_vertex);
}

Skybox::~Skybox(){
}

void Skybox::draw(Camera *camera){
	glDisable(GL_DEPTH_TEST);

	m_texture->bind();
	// we don't use viewInverted because the skybbox does not travel with the camera
	m_shaderProgram->setUniform("viewInverted", glm::mat4_cast(glm::inverse(camera->orientation())));
	m_shaderProgram->setUniform("projection", camera->projection());
	m_shaderProgram->use();

	m_vertexArrayObject->drawArrays(GL_TRIANGLE_FAN, 0, 4);

	m_shaderProgram->release();
	m_texture->unbind();

	glEnable(GL_DEPTH_TEST);
}