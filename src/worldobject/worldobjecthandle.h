#pragma once

class WorldObject;

/* 
 contains a pointer to a worldobject
 use this handle if it is possible that 
 the worldobject gets deleted. check if
 the handle is still valid if you access it
*/
class WorldObjectHandle {

public:   
    WorldObjectHandle(WorldObject* worldObject);
    void invalidate();

    // returns WorldObject* or nullptr
    WorldObject* get();

protected:


    WorldObject* m_worldObject;
};