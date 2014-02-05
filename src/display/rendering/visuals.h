#pragma once

#include <stdint.h>


/*
	Provides all attributes needed to render *something*
	with all currently implemented visual effects
*/
class Visuals {
public:
	Visuals();
	Visuals(uint32_t color, float emissiveness);

	uint32_t color() const;
	void setColor(uint32_t color);

	float emissiveness() const;
	void setEmissiveness(float emissiveness);



protected:
	uint32_t m_color;
	float m_emissiveness;
};

