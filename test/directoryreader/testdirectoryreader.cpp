
#include <bandit/bandit.h>

#include <iostream>
#include <list>
#include <string>

#include "property/propertymanager.h"

#include "utils/directoryreader.h"



using namespace bandit;


go_bandit([](){
    describe("DirectoryReader", [](){
        PropertyManager::instance()->reset();
        PropertyManager::instance()->load("data/config.ini");
        PropertyManager::instance()->load("data/voxels.ini", "voxels");

        std::string pathBase = "test/directoryreader/test/";

        it("reads directory", [&]() {
            DirectoryReader r(pathBase);
            std::list<std::string> files = r.read();

            AssertThat(files.size(), Equals(3));

            AssertThat(files, Contains(pathBase + "ab_-c.txt"));
            AssertThat(files, Contains(pathBase + "awesometestrly"));
            AssertThat(files, Contains(pathBase + "lulz.mp3"));
        });

        it("doesn't care about missing slash at the end", [&]() {
            DirectoryReader r(pathBase.substr(0, pathBase.size()-1));

            std::list<std::string> files = r.read();

            AssertThat(files.size(), Equals(3));

            AssertThat(files, Contains(pathBase + "ab_-c.txt"));
            AssertThat(files, Contains(pathBase + "awesometestrly"));
            AssertThat(files, Contains(pathBase + "lulz.mp3"));
        });
    });
});

