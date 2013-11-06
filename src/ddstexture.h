#pragma once
#include <string>

#include <glow/Texture.h>

class DdsTexture
{
public:
	static bool loadImage2d(glow::Texture * texture, std::string path);
	static bool loadImage2d(glow::Texture * texture, std::string path, GLenum targetOverride);

	// The texture must have target GL_TEXTURE_CUBE_MAP
	static bool DdsTexture::loadImageCube(glow::Texture * texture, std::string pathXp, std::string pathXn,
		std::string pathYp, std::string pathYn, std::string pathZp, std::string pathZn);


private:
    const static int FOURCC_DXT1 = 0x31545844;
    const static int FOURCC_DXT2 = 0x32545844;
    const static int FOURCC_DXT3 = 0x33545844;
    const static int FOURCC_DXT4 = 0x34545844;
    const static int FOURCC_DXT5 = 0x35545844;
};

