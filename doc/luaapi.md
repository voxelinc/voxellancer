#Lua API bindings
generated from 0a672ff


## aibindings.h
```c
apikey createFlyToTask(apikey ship);
int setTargetPoint(apikey flyToTask, float x, float y, float z);
```
## commonbindings.h
```c
bool isKeyValid(apikey key);
int showText(const std::string& string);
int showTextFor(const std::string& string, int seconds);
float getFactionRelation(const std::string& factionA, const std::string& factionB);
int setFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness);
int setEventActive(apikey eventPoll, bool active);
apikey createSingleShotTimer(const std::string& callback, float delta);
apikey createLoopingTimer(const std::string& callback, float delta);
apikey onAABBEntered(apikey worldObject, glm::vec3 llf, glm::vec3 urb, const std::string& callback);
apikey onWorldObjectDestroyed(apikey worldObject, const std::string& callback);
```
## worldobjectbindings.h
```c
apikey playerShip();
apikey createShip(const std::string& name);
int spawn(apikey worldObject);
int setPosition(apikey worldObject, float x, float y, float z);
int setOrientation(apikey worldObject, float x, float y, float z);
glm::vec3 position(apikey worldObject);
glm::vec3 orientation(apikey worldObject);
```
