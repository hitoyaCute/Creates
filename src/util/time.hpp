#pragma once

#include <chrono>
// #include <ratio>
#include <ratio>
#include <unistd.h>

struct Time {
public:
    // get the current time
    const double time() const {
        auto now = std::chrono::system_clock::now();
        return std::chrono::duration<double, std::milli>(now.time_since_epoch()).count() / 1000.f;
    }

    const void sleep(float duration) const {
        usleep(duration * 1000000);
    }
};



