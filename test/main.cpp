#include <thread>
#include <chrono>

#include <bandit/bandit.h>

using namespace bandit;


int main(int argc, char* argv[]) {
    int result = bandit::run(argc, argv);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    return result;
}


