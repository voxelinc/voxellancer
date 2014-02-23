#include <bandit/bandit.h>

#include "utils/threadpool.h"


using namespace bandit;

void increment(int& i) {
    i++;
}


go_bandit([]() {
    describe("ThreadPool", []() {


        before_each([&]() {
        });

        after_each([&]() {
        });

        it("can work on an array", [&]() {
            ThreadPool<int> pool(increment);
            std::vector<int> ints(10000);
            pool.map(ints);
            for (int i = 0; i < ints.size(); i++) {
                AssertThat(ints[i], Equals(1));
            }
        });

    });

});
    