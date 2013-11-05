#pragma once


class FloatProperty {

public:
    FloatProperty(char * name);
    virtual ~FloatProperty();

    operator float();

    char * name();
    float get();
    void set(float value);
    char * m_name;

private:
    float m_value;
};