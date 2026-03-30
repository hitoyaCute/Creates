#pragma once

#include <algorithm>

namespace cUtils {



////////////////////////////////////////////////////////////
/// \bound this will bound a value to a certain value
///
///
/// \param val the value will be bounded
/// \upper the ceiling
/// \lower the floor
///  
///
/// \return the bounded value 
////////////////////////////////////////////////////////////
template <typename comperable>
inline constexpr comperable bound(const comperable& val, const comperable& upper, const comperable& lower) {
    return std::min(std::max(val, lower), upper);
}

}

