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

        it("reads directory", [&]() {
            std::string pathBase = "test/directoryreader/test";

            DirectoryReader r(pathBase);
            std::list<std::string> files = r.read();

            AssertThat(files.size(), Equals(3));


            AssertThat(std::find(files.begin(), files.end(), pathBase + "/ab_-c.txt"), !Equals(files.end()));
            AssertThat(std::find(files.begin(), files.end(), pathBase + "/awesometestrly"), !Equals(files.end()));
            AssertThat(std::find(files.begin(), files.end(), pathBase + "/lulz.mp3"), !Equals(files.end()));
        });

        it("doesn't care about slash at the end", [&]() {
            std::string pathBase = "test/directoryreader/test/";
            DirectoryReader r(pathBase);

            std::list<std::string> files = r.read();

            AssertThat(files.size(), Equals(3));
            AssertThat(std::find(files.begin(), files.end(), pathBase + "ab_-c.txt"), !Equals(files.end()));
            AssertThat(std::find(files.begin(), files.end(), pathBase + "awesometestrly"), !Equals(files.end()));
            AssertThat(std::find(files.begin(), files.end(), pathBase + "lulz.mp3"), !Equals(files.end()));
        });
    });
});

