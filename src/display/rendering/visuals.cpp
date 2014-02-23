#include "visuals.h"

#include "property/property.h"


Visuals::Visuals():
    m_color(0xFF0080FF), // You are urged to alter this.
    m_emissiveness(0.0f)
{
}

Visuals::Visuals(uint32_t color, float emissiveness):
    m_color(color),
    m_emissiveness(emissiveness)
{
}

uint32_t Visuals::color() const {
    return m_color;
}

void Visuals::setColor(uint32_t color) {
    m_color = color;
}

float Visuals::emissiveness() const {
    return m_emissiveness;
}

void Visuals::setEmissiveness(float emissiveness) {
    m_emissiveness = emissiveness;
}

Visuals Visuals::fromProperties(const std::string& prefix) {
    return Visuals(
        Property<uint32_t>::get(prefix + ".color"),
        Property<float>::get(prefix + ".emissiveness")
    );
}

