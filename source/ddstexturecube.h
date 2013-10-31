#pragma once
#include <string>

#include <glow/Texture.h>

class DdsTextureCube
{
public:
	static glow::Texture * load(std::string pathXp, std::string pathXn, std::string pathYp, std::string pathYn, std::string pathZp, std::string pathZn);

private:
	static void loadSingleTexture(std::string path, glow::Texture *texture, GLenum target);
private:
    const static int FOURCC_DXT1 = 0x31545844;
    const static int FOURCC_DXT2 = 0x32545844;
    const static int FOURCC_DXT3 = 0x33545844;
    const static int FOURCC_DXT4 = 0x34545844;
    const static int FOURCC_DXT5 = 0x35545844;
};

