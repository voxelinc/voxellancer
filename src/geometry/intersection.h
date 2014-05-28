#pragma once


class Intersection {
public:
    Intersection();
    Intersection(bool is);
    virtual ~Intersection();

    bool is() const;

    operator bool() const;


protected:
    bool m_is;
};

