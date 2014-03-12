#include <bandit/bandit.h>

#include <memory>

#include "../bandit_extension/vec3helper.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"
#include "player.h"
#include "property/propertydirectory.h"
#include "property/propertymanager.h"
#include "scripting/scriptengine.h"
#include "scripting/gameplayscript.h"
#include "world/world.h"
#include "worldobject/worldobject.h"
#include "worldobject/ship.h"


using namespace bandit;


go_bandit([](){
    describe("Scripting", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");
        PropertyDirectory("data/worldobjects").read();
        PropertyDirectory("data/equipment/engines").read();
        PropertyDirectory("data/equipment/weapons").read();
        PropertyDirectory("data/equipment/projectiles").read();

        std::unique_ptr<ScriptEngine> scriptEngine;
        std::unique_ptr<GamePlayScript> script;

        before_each([&](){
            World::reset(false);
            scriptEngine.reset(new ScriptEngine(World::instance()));
            script.reset(new GamePlayScript(scriptEngine.get()));
        });

        it("can set debug status", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( 
                setDebugStatus("success") 
            )");
            AssertThat(script->debugStatus(), Equals("success"));
        });

        it("can spawn ships", [&]() {
            script->loadString(R"( 
                ship = createShip("basicship")
                spawn(ship)
            )");

            AssertThat(World::instance()->ships().size(), Equals(1));
        });

        it("can access non existing playership", [&]() {
            script->loadString(R"( 
                ship = playerShip()
                setDebugStatus(ship)
            )");

            AssertThat(script->debugStatus(), Equals("0"));
        });

        it("can access unscriptable playership", [&]() {
            World::instance()->player().setShip(new Ship);
            script->loadString(R"( 
                ship = playerShip()
                setDebugStatus(ship)
            )");

            AssertThat(script->debugStatus(), Equals("-1"));
        });


        it("can access scriptable playership", [&]() {
            Ship* ship = new Ship();
            ship->setScriptKey(1337);
            World::instance()->player().setShip(ship);
            script->loadString(R"( 
                ship = playerShip()
                setDebugStatus(ship)
            )");

            AssertThat(script->debugStatus(), Equals("1337"));
        });

        it("can access positions", [&]() {
            Ship* ship = new Ship();
            ship->transform().setPosition(glm::vec3(4, 5, 6));
            scriptEngine->registerScriptable(ship);
            World::instance()->player().setShip(ship);
            script->loadString(R"( 
                ship = playerShip()
                p = position(ship)
                setDebugStatus(p.x*100 + p.y*10 + p.z)
            )");

            AssertThat(script->debugStatus(), Equals("456"));
        });

        it("can set positions", [&]() {
            Ship* ship = new Ship();
            scriptEngine->registerScriptable(ship);
            World::instance()->player().setShip(ship);
            script->loadString(R"( 
                ship = playerShip()
                setPosition(ship, vec3(7,8,9))
            )");

            AssertThat(ship->position(), Equals(glm::vec3(7,8,9)));
        });

    });
 
});

