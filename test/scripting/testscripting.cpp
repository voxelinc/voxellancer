#include <bandit/bandit.h>

#include <memory>

#include "../bandit_extension/vec3helper.h"

#include "ai/squad.h"
#include "ai/character.h"
#include "ai/aitask.h"
#include "ai/basictasks/fighttask.h"
#include "ai/grouptasks/patrolwaypointstask.h"
#include "ai/squadlogic.h"
#include "ai/grouptasks/defendareatask.h"

#include "events/eventpoller.h"

#include "gamestate/game.h"
#include "gamestate/gameplay/gameplay.h"

#include "player.h"

#include "property/propertydirectory.h"
#include "property/propertymanager.h"

#include "scripting/scriptengine.h"
#include "scripting/gameplayscript.h"

#include "voxel/voxel.h"

#include "world/world.h"
#include "worldobject/worldobject.h"
#include "worldobject/ship.h"


using namespace bandit;


go_bandit([](){
    describe("Scripting / GamePlayScript", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");
        PropertyDirectory("data/worldobjects").read();
        PropertyDirectory("data/equipment/engines").read();
        PropertyDirectory("data/equipment/weapons").read();
        PropertyDirectory("data/equipment/projectiles").read();

        std::unique_ptr<ScriptEngine> scriptEngine;
        std::unique_ptr<GamePlayScript> script;
        std::unique_ptr<Player> player;

        std::string callbackFunction = R"( function callback() setDebugStatus("callback!") end )";


        before_each([&](){
            World::reset(false);
            player.reset(new Player());
            World::instance()->setPlayer(*player);
            scriptEngine.reset(new ScriptEngine(World::instance()));
            script.reset(new GamePlayScript(scriptEngine.get()));
            script->loadString(callbackFunction);
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

        describe("with ship", [&]() {
            std::unique_ptr<Ship> ship;

            before_each([&]() {
                ship.reset(new Ship());
                World::instance()->player().setShip(ship.get());
                scriptEngine->registerScriptable(ship.get());
            });


            it("can access unscriptable playership", [&]() {
                scriptEngine->unregisterScriptable(ship.get());
                script->loadString(R"(
                    ship = playerShip()
                    setDebugStatus(ship)
                )");

                AssertThat(script->debugStatus(), Equals("-1"));
            });


            it("can access scriptable playership", [&]() {
                script->loadString(R"(
                    ship = playerShip()
                    setDebugStatus(ship)
                )");

                AssertThat(atoi(script->debugStatus().c_str()), Equals(ship->scriptKey()));
            });

            it("can access positions", [&]() {
                ship->transform().setPosition(glm::vec3(4, 5, 6));
                script->loadString(R"(
                    ship = playerShip()
                    p = position(ship)
                    setDebugStatus(p.x*100 + p.y*10 + p.z)
                )");

                AssertThat(script->debugStatus(), Equals("456"));
            });

            it("can set positions", [&]() {
                script->loadString(R"(
                    ship = playerShip()
                    setPosition(ship, vec3(7,8,9))
                )");

                AssertThat(ship->position(), Equals(glm::vec3(7,8,9)));
            });

            it("can set positions", [&]() {
                script->loadString(R"(
                    ship = playerShip()
                    setPosition(ship, vec3(7,8,9))
                )");

                AssertThat(ship->position(), Equals(glm::vec3(7, 8, 9)));
            });

            it("can poll aabb", [&]() {
                script->loadString(R"(
                    onAABBEntered(playerShip(), vec3(-50,-50,-150), vec3(50,50,-100), "callback")
                )");
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));

                ship->transform().setPosition(glm::vec3(0, 0, -110));
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals("callback!"));

                script->apiSetDebugStatus("");
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));
            });

            it("can poll flyto finished", [&]() {
                script->loadString(R"(
                    task = createFlyToTask(playerShip())
	                setTargetPoint(task, vec3(0, 0, 10))
                    onAiTaskFinished(task, "callback")
                )");
                AssertThat(ship->character()->task()->isFinished(), Equals(false));

                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));

                ship->transform().setPosition(glm::vec3(0, 0, 9.8));
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals("callback!"));

                script->apiSetDebugStatus("");
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));
            });

            it("can poll destruction", [&]() {
                ship->addVoxel(new Voxel(glm::ivec3(1, 2, 3)));
                ship->setCrucialVoxel(glm::ivec3(1, 2, 3));
                script->loadString(R"(
                    onWorldObjectDestroyed(playerShip(), "callback")
                )");

                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));

                ship->removeVoxel(ship->crucialVoxel());
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals("callback!"));
            });

            it("can poll destruction on deleted ship", [&]() {
                ship->addVoxel(new Voxel(glm::ivec3(1, 2, 3)));
                script->loadString(R"(
                    onWorldObjectDestroyed(playerShip(), "callback")
                )");

                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals(""));

                ship.reset(nullptr);
                World::instance()->eventPoller().update(1.0f);
                AssertThat(script->debugStatus(), Equals("callback!"));
            });


            it("can set fighttask", [&]() {
                script->loadString(R"(
                    task = createFightTask(playerShip())
                    target = createShip("basicship")
	                addFightTaskTarget(task, target)
                )");

                FightTask* fightTask = dynamic_cast<FightTask*>(ship->character()->task().get());
                AssertThat(fightTask->targets().size(), Equals(1));

            });

            it("can create squads", [&]() {
                script->loadString(R"(
                    createSquad(playerShip())
                )");

                AssertThat(ship->squadLogic()->inSquad(), Equals(true));
                AssertThat(ship->squadLogic()->isSquadLeader(), Equals(true));
                AssertThat(ship->squadLogic()->squad()->members().size(), Equals(0)); // squad leader is not member!?
            });

            it("can add ships to squads", [&]() {
                script->loadString(R"(
                    squad = createSquad(playerShip())
                    s1 = createShip("basicship")
                    s2 = createShip("basicship")
                    joinSquad(squad, s1)
                    joinSquad(squad, s2)
                )");

                AssertThat(ship->squadLogic()->isSquadLeader(), Equals(true));
                AssertThat(ship->squadLogic()->squad()->members().size(), Equals(2));
            });

            it("can create patrolwaypoint task with squads", [&]() {
                script->loadString(R"(
                    squad = createSquad(playerShip())
                    createPatrolWaypointsTask(squad)
                )");

                AiGroupTask* task = ship->squadLogic()->squad()->task().get();
                AssertThat(task != nullptr, IsTrue());
            });

            it("can add waypoints to patrolwaypointtask", [&]() {
                script->loadString(R"(
                    squad = createSquad(playerShip())
                    task = createPatrolWaypointsTask(squad)
                    addPatrolwWaypointPoint(task, vec3(1,2,3))
                )");

                PatrolWaypointsTask* task = dynamic_cast<PatrolWaypointsTask*>(ship->squadLogic()->squad()->task().get());
                AssertThat(*task->currentTargetPoint(), EqualsWithDelta(glm::vec3(1,2,3), 0.001f));
            });

            it("can create defend area task with squads", [&]() {
                script->loadString(R"(
                    squad = createSquad(playerShip())
                    createDefendAreaTask(squad, vec3(1,2,3), 3.14)
                )");

                DefendAreaTask* defendTask = dynamic_cast<DefendAreaTask*>(ship->squadLogic()->squad()->task().get());

                AssertThat(defendTask != nullptr, IsTrue());
                AssertThat(defendTask->points().front(), EqualsWithDelta(glm::vec3(1, 2, 3), 0.001f));
                AssertThat(defendTask->range(), EqualsWithDelta(3.14f, 0.001f));

            });

            it("can add waypoints to defend area task", [&]() {
                script->loadString(R"(
                    squad = createSquad(playerShip())
                    task = createDefendAreaTask(squad, vec3(1,2,3), 3.14)
                    addDefendAreaPoint(task, vec3(3,4,5))
                )");

                DefendAreaTask* task = dynamic_cast<DefendAreaTask*>(ship->squadLogic()->squad()->task().get());

                AssertThat(task->points().size(), Equals(2));
                AssertThat(task->points().front(), EqualsWithDelta(glm::vec3(1, 2, 3), 0.001f));
                AssertThat(task->points().back(), EqualsWithDelta(glm::vec3(3, 4, 5), 0.001f));
            });
        });
    });
});

