#include "ddstexture.h"

#include <fstream>
#include <string.h>

#include <glow/logging.h>
#include <glow/Texture.h>


bool DdsTexture::loadImage2d(glow::Texture * texture, std::string path){
    assert(texture->target() != GL_TEXTURE_CUBE_MAP);
    return loadImage2d(texture, path, texture->target());
}

bool DdsTexture::loadImageCube(glow::Texture * texture, std::string pathXp, std::string pathXn,
    std::string pathYp, std::string pathYn, std::string pathZp, std::string pathZn){
    assert(texture->target() == GL_TEXTURE_CUBE_MAP);

    /* load all six textures */
    if (!loadImage2d(texture, pathXp, GL_TEXTURE_CUBE_MAP_POSITIVE_X)) return false;
    if (!loadImage2d(texture, pathXn, GL_TEXTURE_CUBE_MAP_NEGATIVE_X)) return false;
    if (!loadImage2d(texture, pathYp, GL_TEXTURE_CUBE_MAP_POSITIVE_Y)) return false;
    if (!loadImage2d(texture, pathYn, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)) return false;
    if (!loadImage2d(texture, pathZp, GL_TEXTURE_CUBE_MAP_POSITIVE_Z)) return false;
    if (!loadImage2d(texture, pathZn, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)) return false;

    return true;
}

bool DdsTexture::loadImage2d(glow::Texture * texture, std::string path, GLenum target)
{
    char header[124];

    /* try to open the file */
    std::ifstream file(path, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        glow::fatal("DdsTexture: could not read: %;", path);
        return false;
    }

    file.seekg(0, std::ios::beg);

    /* verify the type of file */
    char filecode[4];
    file.read(filecode, 4);

    if (strncmp(filecode, "DDS ", 4) != 0) {
        file.close();
        glow::critical("DdsTexture: not a dds file: %;", path);
        return false;
    }

    /* get the surface desc */
    file.read(header, 124);

    unsigned int height = *(unsigned int*)&(header[8]);
    unsigned int width = *(unsigned int*)&(header[12]);
    unsigned int linearSize = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC = *(unsigned int*)&(header[80]);

    /* how big is it going to be including all mipmaps? */
    unsigned int bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    char * buffer = new char[bufsize * sizeof(char)];
    file.read(buffer, bufsize);
    /* close the file pointer */
    file.close();

    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        delete[] buffer;
        glow::critical("DdsTexture: not a supported dds format: %", path);
        return false;
    }

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
        texture->compressedImage2D(level, format, width, height, 0, size, buffer + offset, target);
        offset += size;
        width /= 2;
        height /= 2;
    }
    delete[] buffer;

    return true;
}

