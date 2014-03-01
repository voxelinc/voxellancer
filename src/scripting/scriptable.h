#pragma once


enum class ScriptableType {
    Squad,
    WorldObject,
    Ship,
    Other
};

class Scriptable {
public:
    Scriptable();

    virtual ScriptableType scriptableType() const = 0;

    int scriptKey() const;
    void setScriptKey(int key);


protected:
    int m_key;
};

