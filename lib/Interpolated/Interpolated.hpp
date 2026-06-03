#pragma once

#include <chrono>
#include <type_traits>
namespace Interpolation {


enum Easing : char {
    None,
    linear,
    easeInBack,
    easeInElastic,
    easeInOutElastic,
    easeInOutExponential,
    easeOutBack,
    easeOutElastic
};

const float getRatio(const float t, const Easing transition);

template <typename T>
requires std::is_arithmetic_v<T>
struct Interpolated {
    // starting value
    T start{};
    // target value
    T end{};

    // the time when the transition starts
    float initial_time{};

    float speed{1.f};
   
    // get the time have passed after the transition
    [[nodiscard]] static float getCurrentTime(){
        // get current time
        const auto now = std::chrono::steady_clock::now();
        const auto duration = now.time_since_epoch();
        // convert to float
        const auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(duration);
        return seconds.count();
    }

    // get the time elapsed since the last value change
    [[nodiscard]] float getElapsedSec() const {
        return getCurrentTime() - initial_time;
    }
    
    void setValue(const T& new_val){
        start = getValue();
        end = new_val;
        initial_time = getCurrentTime();
    }
    
    // return the current value
    [[nodiscard]] T getValue() const {
        // current transition time
        const float elapsed = getElapsedSec();
        // when transition is done, return final
        
        const float t = elapsed * speed;

        if (t >= 1.0f) {return end;}

        // compute interpolated value
        const T delta{static_cast<T>(end - start)};
        return start + delta * getRatio(t, transition);
    } 

    Easing transition;
    Interpolated(const T& initial_val = {}):
        start{initial_val},
        end{initial_val},
        transition{Easing::linear}{}
    Interpolated(const T& initial_val, const Easing func):
        start{initial_val},
        end{initial_val},
        transition(func){}
    Interpolated(const T& initial_val, const float duration, const Easing func = linear):
        start{initial_val},
        end{initial_val},
        transition(func){setDuration(duration);}

    void setDuration(float duration) {
        speed = 1.f / duration;
    }

    T get_start() const {
        return start;
    }
    T get_end() const {
        return end;
    }

    // reset everything and return the value to the start
    void reset(const T& val) {
        initial_time = getCurrentTime();
        start = val;
        end = val;
    }

    // cast operator
    [[nodiscard]] operator T() const {
        return getValue();
    }

    // setter operator
    void operator=(const T& new_val){
        setValue(new_val);
    }

};

namespace EasingFunc {
    const float easeInBack(const float t);
    const float easeInOutExponential(const float t);
    const float easeOutBack(const float t);
    const float easeOutElastic(const float t);
    const float easeInElastic(const float t);
    const float easeInOutElastic(const float t);
};


// Actuator
//
// moves between 2 values
template <typename T>
struct Actuator {
    Interpolated<T> value;
    T t_a;
    T t_b;

    float duration_a;
    float duration_b;

    Easing a_t_b = Easing::linear;
    Easing b_t_a = Easing::linear;

    // idk why i put this here...
    bool is_B_to_A = 0;

    Actuator() = delete;
    Actuator(const T a, const T b, float t): t_a{a}, t_b{b}, duration_a{t}, duration_b{t} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }
    Actuator(const T a, const T b, float time_a, float time_b): t_a{a}, t_b{b}, duration_a{time_a}, duration_b{time_b} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }
    Actuator(const T a, const T b, float t, Easing easing): t_a{a}, t_b{b}, duration_a{t}, duration_b{t}, a_t_b{easing}, b_t_a{easing} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }
    Actuator(const T a, const T b, float time_a, float time_b, Easing easing): t_a{a}, t_b{b}, duration_a{time_a}, duration_b(time_b), a_t_b{easing}, b_t_a{easing} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }
    Actuator(const T a, const T b, float t, Easing easing_a, Easing easing_b): t_a{a}, t_b{b}, duration_a{t}, duration_b{t}, a_t_b{easing_a}, b_t_a{easing_b} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }
    Actuator(const T a, const T b, float time_a, float time_b, Easing easing_a, Easing easing_b): t_a{a}, t_b{b}, duration_a{time_a}, duration_b{time_b}, a_t_b{easing_a}, b_t_a{easing_b} {
        value = Interpolated<T>{a, duration_a, a_t_b};
    }

    void setForward() {
        value = t_b;
        value.transition = a_t_b;
        value.setDuration(duration_a);
        is_B_to_A = 0;
    }
    void setBackward() {
        value.transition = b_t_a;
        value.setDuration(duration_b);
        value = t_a;
        is_B_to_A = 1;
    }

    operator const T() const {
        return T{value};
    }
};


}; // namespace Interpolation




