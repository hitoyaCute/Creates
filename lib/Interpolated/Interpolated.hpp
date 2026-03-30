#pragma once

#include <chrono>
#include <type_traits>
namespace Interpolation {


enum Easing {
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
class Interpolated {
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

public:
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

}; // namespace Interpolation
//
//


