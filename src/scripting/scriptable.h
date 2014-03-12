#pragma once


class Scriptable {
public:
    Scriptable();
    virtual ~Scriptable();

    int scriptKey() const;
    void setScriptKey(int key);

    static const int INVALID_KEY = -1;

protected:
    int m_key;
};

