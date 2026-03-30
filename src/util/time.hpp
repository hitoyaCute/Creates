#pragma once

#include <chrono>
#include <ratio>
#include <unistd.h>

inline struct Time {
public:
    // get the current time
    static inline double time() {
        const auto now = std::chrono::system_clock::now();
        return std::chrono::duration<double, std::milli>(now.time_since_epoch()).count() / 1000.f;
    }

    static inline void sleep(float duration) {
        usleep(duration * 1000000);
    }
} Time;



