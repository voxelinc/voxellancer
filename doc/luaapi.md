#Lua API bindings
generated from 01772b3


## aibindings.h
```c
std::string getFaction(apikey ship);
int setFaction(apikey ship, const std::string& faction);
float getFactionRelation(const std::string& factionA, const std::string& factionB);
int setFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness);
apikey onAiTaskFinished(apikey aiTask, const std::string& callback);
apikey createFlyToTask(apikey ship);
int setTargetPoint(apikey flyToTask, const glm::vec3& point);
apikey createFightTask(apikey ship);
int addFightTaskTarget(apikey flyToTask, apikey worldObject);
```

## commonbindings.h
```c
bool isKeyValid(apikey key);
int showText(const std::string& string);
int showTextFor(const std::string& string, int seconds);
int setEventActive(apikey eventPoll, bool active);
apikey createSingleShotTimer(const std::string& callback, float delta);
apikey createLoopingTimer(const std::string& callback, float delta);
apikey onAABBEntered(apikey worldObject, const glm::vec3& llf, const glm::vec3& urb, const std::string& callback);
```

## squadbindings.h
```c
apikey createSquad(apikey leader);
int createPatrolWaypointsTask(apikey squad);
int addPatrolwWaypointPoint(apikey task, const glm::vec3& point);
int joinSquad(apikey squad, apikey ship);
```

## worldobjectbindings.h
```c
apikey playerShip();
apikey createShip(const std::string& name);
int spawn(apikey worldObject);
int setPosition(apikey worldObject, const glm::vec3& position);
int setOrientation(apikey worldObject, const glm::vec3& orientation);
glm::vec3 position(apikey worldObject);
glm::vec3 orientation(apikey worldObject);
apikey onWorldObjectDestroyed(apikey worldObject, const std::string& callback);
```
