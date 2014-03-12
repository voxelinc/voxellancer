#include <bandit/bandit.h>

#include "../bandit_extension/vec3helper.h"

#include "scripting/gameplayscript.h"
#include "worldobject/worldobject.h"
#include "property/propertymanager.h"
#include "world/world.h"
#include "gamestate/gameplay/gameplay.h"
#include "scripting/scriptengine.h"
#include "gamestate/game.h"


using namespace bandit;


go_bandit([](){
    describe("Scripting", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        GamePlayScript* script;

        before_each([&](){
            World::reset();
            script = new GamePlayScript(new ScriptEngine(World::instance()));
        });

        it("debug status works", [&]() {
            AssertThat(script->debugStatus(), Equals(""));
            script->loadString(R"( setDebugStatus("success") )");
            AssertThat(script->debugStatus(), Equals("success"));
        });
    });
});

