#pragma once
#include <string>

#include <gl/glew.h>

namespace glow {
    class Texture;
}


class DdsTexture
{
public:
	static bool loadImage2d(glow::Texture * texture, std::string path);

	static bool loadImageCube(glow::Texture * texture, std::string pathXp, std::string pathXn,
		std::string pathYp, std::string pathYn, std::string pathZp, std::string pathZn);

private:
    static bool loadImage2d(glow::Texture * texture, std::string path, GLenum target);

    const static int FOURCC_DXT1 = 0x31545844;
    const static int FOURCC_DXT2 = 0x32545844;
    const static int FOURCC_DXT3 = 0x33545844;
    const static int FOURCC_DXT4 = 0x34545844;
    const static int FOURCC_DXT5 = 0x35545844;
};

