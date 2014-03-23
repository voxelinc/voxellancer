#include <bandit/bandit.h>

#include <glm/glm.hpp>
#include <glow/ChangeListener.h>
#include <glow/logging.h>

#include <fstream>

#include "property/property.h"
#include "property/propertymanager.h"
#include "input/inputmapping.h"
#include "utils/filesystem.h"
#include "utils/directoryreader.h"

using namespace bandit;





go_bandit([](){
    class Listener : public glow::ChangeListener {
    public:
        bool success = false;

        virtual void notifyChanged(glow::Changeable * sender) override {
            success = true;
        }
    };

    describe("Property", []() {
        before_each([&]() {
            glow::setVerbosityLevel(glow::LogMessage::Fatal);
            PropertyManager::reset();
        });
        after_each([&]() {
            glow::setVerbosityLevel(glow::LogMessage::Info);
        });

        it("should load", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");

            Property<int> iSize("player.size");
            Property<float> fProp("player.size");
            Property<float> fProp2("player.height");
            Property<std::string> sProp1("player.name");
            Property<std::string> sProp2("section.name");
            Property<char> cProp("section.forward");
            Property<bool> bProp2("player.is_true");
            Property<glm::vec3> v3Prop("player.pos");
            Property<float> angleProp("player.angle");

            AssertThat(iSize.get(), Equals(1));
            AssertThat(fProp.get(), Equals(1));
            AssertThat(fProp2.get(), EqualsWithDelta(4.51, 0.01));
            AssertThat(sProp1.get(), Equals("hans"));
            AssertThat(sProp2.get(), Equals("peter"));
            AssertThat(cProp.get(), Equals('w'));
            AssertThat(bProp2.get(), Equals(true));
            AssertThat(v3Prop->x, Equals(1.0));
            AssertThat(v3Prop->y, Equals(0));
            AssertThat(v3Prop->z, Equals(.5));
            AssertThat(angleProp.get(), EqualsWithDelta(glm::radians(45.0f), 0.01));
        });

        it("understands inputmapping", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");

            Property<InputMapping> mapping("mapping.fire");

            AssertThat(mapping->type(), Equals(InputType::Keyboard));
            AssertThat(mapping->index(), Equals(5));
            AssertThat(mapping->maxValue(), EqualsWithDelta(-10.2, 0.01f));
            AssertThat(mapping->idleValue(), EqualsWithDelta(1.3, 0.01f));

        });

        it("should work before load", [&]() {

            Property<int> iSize("player.size", 0);
            AssertThat(iSize.get(), Equals(0));
            Property<float> fProp("player.size", 0);
            Property<float> fProp2("player.height", 0);
            Property<std::string> sProp1("player.name", "");
            Property<std::string> sProp2("section.name", "");
            Property<char> cProp("section.forward", ' ');
            Property<bool> bProp2("player.is_true", false);

            PropertyManager::instance()->load("test/property/test.ini");

            AssertThat(iSize.get(), Equals(1));
            AssertThat(fProp.get(), Equals(1));
            AssertThat(fProp2.get(), EqualsWithDelta(4.51, 0.01));
            AssertThat(sProp1.get(), Equals("hans"));
            AssertThat(sProp2.get(), Equals("peter"));
            AssertThat(cProp.get(), Equals('w'));
            AssertThat(bProp2.get(), Equals(true));

        });

        it("should reload", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");
            Property<std::string> sProp("player.name");
            Property<char> cProp("section.forward");

            AssertThat(sProp.get(), Equals("hans"));
            AssertThat(cProp.get(), Equals('w'));

            PropertyManager::instance()->load("test/property/test2.ini");
            AssertThat(sProp.get(), Equals("hans meier"));
            AssertThat(cProp.get(), Equals('x'));
        });

        it("should call a callback", [&]() {
            PropertyManager::instance()->load("test/property/test.ini");

            Listener listener;
            PropertyManager::instance()->registerListener(&listener);
            AssertThat(listener.success, Equals(false));
            PropertyManager::instance()->load("test/property/test.ini");
            AssertThat(listener.success, Equals(true));

            PropertyManager::instance()->deregisterListener(&listener);

        });
    });

    describe("FilesSystem",[&]() {
        it("has a user config dir", [&]() {
            std::string dir = FileSystem::userConfigDir();
            AssertThat(dir, !Equals(""));
            AssertThat(FileSystem::exists(dir), Equals(true));
        });

        it("can copy files", [&]() {
            std::string source = "test/property/test.ini";
            std::string target = FileSystem::userConfigDir() + "/test.ini";
            if (FileSystem::exists(target)) {
                FileSystem::removeFile(target);
            }

            AssertThat(FileSystem::exists(source), Equals(true));
            AssertThat(FileSystem::exists(target), Equals(false));

            FileSystem::copyFile(source, target);

            AssertThat(FileSystem::exists(target), Equals(true));

            FileSystem::removeFile(target);

            AssertThat(FileSystem::exists(target), Equals(false));
        });

        it("can create dirs", [&]() {
            std::string dir = FileSystem::userConfigDir() + "/test";
            if (FileSystem::exists(dir)) {
                FileSystem::removeDirectory(dir);
            }
            AssertThat(FileSystem::exists(dir), Equals(false));

            FileSystem::createDirectory(dir);
            AssertThat(FileSystem::exists(dir), Equals(true));

            FileSystem::removeDirectory(dir);
            AssertThat(FileSystem::exists(dir), Equals(false));
        });

        it("can iterate directories", [&]() {
            std::string dir = FileSystem::userConfigDir() + "/test";
            FileSystem::createDirectory(dir);

            std::ofstream(dir + "/test1.txt").close();
            std::ofstream(dir + "/test2.txt").close();
            FileSystem::createDirectory(dir + "/test3");

            DirectoryReader reader(dir);
            std::list<std::string> files = reader.read();

            AssertThat(files.size(), Equals(2));

            FileSystem::removeFile(dir + "/test1.txt");
            FileSystem::removeFile(dir + "/test2.txt");
            FileSystem::removeDirectory(dir + "/test3");
            FileSystem::removeDirectory(dir);
        });
    });
});

