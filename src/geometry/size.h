#pragma once


template<typename T>
class Size {
public:
    Size();
    Size(T width, T height);

    T width() const;
    void setWidth(T width);

    T height() const;
    void setHeight(T height);


protected:
    T m_width;
    T m_height;
};

#include "size.inl"
