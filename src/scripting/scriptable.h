#pragma once


enum class ScriptableType {
    Squad,
    WorldObject,
    Ship,
    EventPoll,
    AiTask,
    Other
};

class Scriptable {
public:
    Scriptable();
    virtual ~Scriptable();

    virtual ScriptableType scriptableType() const = 0;

    int scriptKey() const;
    void setScriptKey(int key);

    static const int INVALID_KEY = -1;

protected:
    int m_key;
};

