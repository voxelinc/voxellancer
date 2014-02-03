#pragma once

class Range {
public:
    Range();
    Range(float min, float max);

    float min() const;
    void setMin(float min);

    float max() const;
    void setMax(float max);

    float clamp(float value);


protected:
    float m_min;
    float m_max;
};
