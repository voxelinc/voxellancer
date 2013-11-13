#include "linuxvmdummy.h"

#include <stdexcept>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>


#include "utils/ddstexture.h"

LinuxVMDummy::LinuxVMDummy() :
	m_shaderProgram(0),
	m_vertexArrayObject(0),
	m_vertexBuffer(0)
{
	/* I can't nail it exactly, but mesa requires some part of this to be executed for the real skybox to be rendered... 
	* these actions do not affect normal operation on "clean" systems because we just initialize some stuff we never use */

	/* Shaders */
	glow::Shader * vertexShader = glow::Shader::fromFile(GL_VERTEX_SHADER, "data/skybox.vert");
	glow::Shader * fragmentShader = glow::Shader::fromFile(GL_FRAGMENT_SHADER, "data/skybox.frag");

	m_shaderProgram = new glow::Program();
	m_shaderProgram->attach(vertexShader, fragmentShader);
	m_shaderProgram->bindFragDataLocation(0, "fragColor");

	m_shaderProgram->getUniform<GLint>("texCube")->set(0);


	/* Geometry */
	auto vertices = glow::Array<glm::vec3>()
		<< glm::vec3(-1, -1, 0)
		<< glm::vec3(1, -1, 0)
		<< glm::vec3(1, 1, 0)
		<< glm::vec3(-1, 1, 0);

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

LinuxVMDummy::~LinuxVMDummy(){
}
