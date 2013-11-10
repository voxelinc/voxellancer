#pragma once

#include <glow/ref_ptr.h>
#include <glow/Texture.h>
#include <glow/Program.h>
#include <glow/VertexArrayObject.h>
#include <glow/Buffer.h>

#include "property/property.h"

/*
* This solves a problem where the hd3000 has only 2fps with 1000 instanced cubes.
* I have no idea why this is happening
*/
class HD3000Dummy
{
public:
    HD3000Dummy();
    ~HD3000Dummy();

    void drawIfActive();

private:
    Property<bool> m_usedummy;
    glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
    glow::ref_ptr<glow::Buffer> m_vertexBuffer;

};

