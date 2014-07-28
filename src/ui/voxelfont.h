#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "voxelfontconstants.h"

class Letter;
class VoxelRenderer;

class VoxelFont {
public:
    VoxelFont();
    ~VoxelFont();

    // renderer must be prepared
    void drawString(std::string text, glm::vec3 position, glm::quat orientation, FontSize size = FontSize::SIZE5x7, float scale = 1.f, FontAlign align = FontAlign::CENTER);

    int letterWidth(FontSize size);
    int letterHeight(FontSize size);

    static VoxelFont* instance();


protected:
    static VoxelFont* s_instance;

    void loadFont(const std::string& identifier, glm::vec3 offset, std::map<char, std::unique_ptr<Letter>> *map);
    void loadChar(const std::string& filename, glm::vec3 offset, const char index, std::map<char, std::unique_ptr<Letter>> *map);

    std::map<char, std::unique_ptr<Letter>> m_font3x5;
    std::map<char, std::unique_ptr<Letter>> m_font5x7;
};

