#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

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

    std::vector<Letter*> letters(std::string text, FontSize size, float scale, FontAlign align);

    // renderer must be prepared
    void drawString(std::string text, glm::vec3 position, FontSize size = s3x5, float scale = 1.f, FontAlign align = aLeft);
    void drawString(std::string text, glm::vec3 position, glm::quat orientation, FontSize size = s3x5, float scale = 1.f, FontAlign align = aLeft);

private:
    void loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<Letter>> *map);
    void loadChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<Letter>> *map);

    std::map<char, std::unique_ptr<Letter>> m_font3x5;
    std::map<char, std::unique_ptr<Letter>> m_font5x7;

    std::vector<Letter*> m_letters;
};
