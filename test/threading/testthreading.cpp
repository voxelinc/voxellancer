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
            ThreadPool<int> pool;
            std::vector<int> ints(10000);

            pool.map(increment, ints);
            for (int i = 0; i < ints.size(); i++) {
                AssertThat(ints[i], Equals(1));
            }

            pool.map(increment, ints, 1452, 4586);
            for (int i = 0; i < 1452; i++) {
                AssertThat(ints[i], Equals(1));
            }
            for (int i = 1452; i < 4586; i++) {
                AssertThat(ints[i], Equals(2));
            }
            for (int i = 4586; i < ints.size(); i++) {
                AssertThat(ints[i], Equals(1));
            }
        });

        it("works as a looping array", [&]() {
            ThreadPool<int> pool;
            std::vector<int> ints(10000);

            pool.map(increment, ints, 9000, 11000);
            for (int i = 0; i < 1000; i++) {
                AssertThat(ints[i], Equals(1));
            }
            for (int i = 1000; i < 9000; i++) {
                AssertThat(ints[i], Equals(0));
            }
            for (int i = 9000; i < ints.size(); i++) {
                AssertThat(ints[i], Equals(1));
            }
        });

    });

});
    