#pragma once
#include <string>
#include <map>
#include <memory>

#include <glm/glm.hpp>

class Letter;
class VoxelRenderer;

enum FontSize {
    s3x5,
    s5x7
};

enum FontAlign {
    aLeft,
    aCenter,
    aRight
};

class VoxelFont {
public:
    VoxelFont();
    ~VoxelFont();

    // renderer must be prepared
    void drawString(std::string text, glm::vec3 position, FontSize size = s3x5, float scale = 1.f, FontAlign align = aLeft);

private:
    void loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<Letter>> *map);
    void loadChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<Letter>> *map);

    std::map<char, std::unique_ptr<Letter>> m_font3x5;
    std::map<char, std::unique_ptr<Letter>> m_font5x7;
};
