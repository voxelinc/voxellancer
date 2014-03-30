Lua API bindings
================
generated from 56f1b4a

## commonbindings.h

    bool valid(apikey key);
    int showMessage(const std::string& string);
    int playVoice(const std::string& soundFile);
    int setEventActive(apikey eventPoll, bool active);
    apikey createSingleShotTimer(const std::string& callback, float delta);
    apikey createLoopingTimer(const std::string& callback, float delta);


## worldobjectbindings.h

    apikey playerShip();
    apikey createShip(const std::string& name);
    apikey createWorldObject(const std::string& name);
    int spawn(apikey worldObject);
    int remove(apikey worldObject);
    int setPosition(apikey worldObject, const glm::vec3& position);
    int setOrientation(apikey worldObject, const glm::vec3& orientation);
    glm::vec3 position(apikey worldObject);
    glm::vec3 orientation(apikey worldObject);
    int setShowOnHud(apikey worldObject, bool show);
    int setCanLockOn(apikey worldObject, bool lockon);
    apikey onWorldObjectDestroyed(apikey worldObject, const std::string& callback);
    apikey onAABBEntered(apikey worldObject, const glm::vec3& llf, const glm::vec3& urb, const std::string& callback);


## externalmissionbindings.h

    apikey missionStart(const std::string& name);
    apikey onMissionFailure(apikey missionKey, const std::string& callback);
    apikey onMissionSuccess(apikey missionKey, const std::string& callback);


## internalmissionbindings.h

    int missionSucceed();
    int missionFail();
    int missionMessage(const std::string& message);
    int missionFailureMessage(const std::string& message);
    int missionSuccessMessage(const std::string& message);


## squadbindings.h

    apikey createSquad(apikey leader);
    int joinSquad(apikey squad, apikey ship);
    int createPatrolWaypointsTask(apikey squad);
    int addPatrolwWaypointPoint(apikey task, const glm::vec3& point);
    int createDefendAreaTask(apikey squad, const glm::vec3& point, float range);
    int addDefendAreaPoint(apikey task, const glm::vec3& point);


## aibindings.h

    std::string getFaction(apikey ship);
    int setFaction(apikey ship, const std::string& faction);
    float getFactionRelation(const std::string& factionA, const std::string& factionB);
    int setFactionRelation(const std::string& factionA, const std::string& factionB, float friendliness);
    apikey onAiTaskFinished(apikey aiTask, const std::string& callback);
    apikey createFlyToTask(apikey ship);
    int setTargetPoint(apikey flyToTask, const glm::vec3& point);
    apikey createFightTask(apikey ship);
    int addFightTaskTarget(apikey flyToTask, apikey worldObject);
    apikey taskExecutor(apikey aiTask);


Ini Objects
===========

## engines

 * candle
 * enginemk1
 * enginemk3
 * loudengine
 * mginemk1
 * piratethruster
 * piratethrusterheavy
 * rocketthrustermk1
 * superslowengine


## bullets

 * gunbullet
 * ionbullet
 * pulselaser_bullet
 * railgunbullet
 * snowball


## rockets

 * hornet


## guns

 * gun
 * ioncannon
 * pulselaser
 * railgun
 * snowcanon


## rocketlaunchers

 * hornetlauncher


## worldobjects

 * banner
 * cake
 * idareyou
 * missionstart


## ships

 * basicship
 * bc304
 * c306
 * eagle
 * f301
 * f302
 * flyingtortress
 * mox
 * normandy
 * piratefrigatte
 * pirategunboat
 * pirateheavy
 * piratelight
 * smallpolice
 * specialbasicship
 * startortress


## colorcodess

 * engineSlot: 0x000E
 * hardpoint: 0x000D
 * cockpit: 0x000C
 * fuel: 0x000F
 * crucial: 0xC00C


