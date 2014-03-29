#pragma once

#include <string>
#include <stdint.h>


/**
*    Provides all attributes needed to render *something*
*    with all currently implemented visual effects
*/
class Visuals {
public:
    Visuals();
    Visuals(uint32_t color, float emissiveness);

    uint32_t color() const;
    void setColor(uint32_t color);

    float emissiveness() const;
    void setEmissiveness(float emissiveness);


    static Visuals fromProperties(const std::string& prefix);


protected:
    uint32_t m_color;
    float m_emissiveness;
};

