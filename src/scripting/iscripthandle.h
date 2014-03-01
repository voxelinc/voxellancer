#pragma once


class Scriptable;

class IScriptHandle {
public:
    virtual bool valid() const = 0;
    virtual void invalidate() = 0;

    virtual Scriptable* scriptable() = 0;
};

