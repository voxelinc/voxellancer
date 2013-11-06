#pragma once

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Thing {
    
public:
    Thing();

    const glm::vec4 center();
    const glm::vec4 up();
    const glm::vec4 direction();

    virtual void draw() = 0;
    virtual void update(float delta_sec);

protected:
    glm::mat4 m_model_matrix;

    glow::ref_ptr<glow::Texture> m_texture;
    glow::ref_ptr<glow::Program> m_shaderProgram;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

};