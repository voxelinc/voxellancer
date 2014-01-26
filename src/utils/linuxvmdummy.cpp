#include "linuxvmdummy.h"

#include <stdexcept>
#include <glow/Shader.h>
#include <glow/VertexAttributeBinding.h>
#include <glowutils/global.h>


#include "resource/ddstexture.h"

/* since the last merge glow attempts to use glCompileShaderIncludeARB if not null.
* while current mesa 9.2.3-2 does not list this extension, this pointer is set -
* to a function that produces empty compiler error messages.
* Thus override Shader::compile() to always use glCompileShader */
bool glow::Shader::compile(){
	glCompileShader(m_id);
	CheckGLError();


	m_compiled = checkCompileStatus();

	if (m_compiled)
		changed();

	return isCompiled();
}

LinuxVMDummy::LinuxVMDummy() :
	m_shaderProgram(0),
	m_vertexArrayObject(0),
	m_vertexBuffer(0)
{
	/* I can't nail it exactly, but mesa requires some part of this to be executed for the real skybox to be rendered... 
	* these actions do not affect normal operation on "clean" systems because we just initialize some stuff we never use */

	/* Shaders */
    glow::Shader * vertexShader = glowutils::createShaderFromFile(GL_VERTEX_SHADER, "data/skybox.vert");
    glow::Shader * fragmentShader = glowutils::createShaderFromFile(GL_FRAGMENT_SHADER, "data/skybox.frag");

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
