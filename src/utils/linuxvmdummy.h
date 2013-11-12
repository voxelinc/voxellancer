#pragma once
#include "glow/ref_ptr.h"
#include "glow/Texture.h"
#include "glow/Program.h"
#include "glow/VertexArrayObject.h"
#include "glow/Buffer.h"

#include "property/property.h"

class LinuxVMDummy {
public:
	LinuxVMDummy();
	virtual ~LinuxVMDummy();
	
protected:
	Property<bool> m_usedummy;

	glow::ref_ptr<glow::Program> m_shaderProgram;
	glow::ref_ptr<glow::VertexArrayObject> m_vertexArrayObject;
	glow::ref_ptr<glow::Buffer> m_vertexBuffer;
};