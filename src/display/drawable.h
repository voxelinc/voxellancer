#pragma once



class Drawable {
public:
    Drawable();

    float emissiveness() const;
    void setEmissiveness(float emissiveness);


protected:
    float m_emissiveness;
};

