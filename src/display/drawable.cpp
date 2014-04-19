#include "drawable.h"


Drawable::Drawable():
    m_emissiveness(0.0f)
{

}

float Drawable::emissiveness() const {
    return m_emissiveness;
}

void Drawable::setEmissiveness(float emissiveness) {
    m_emissiveness = emissiveness;
}
