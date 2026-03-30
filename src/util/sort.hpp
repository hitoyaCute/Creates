#pragma once
#pragma GCC diagnostic error "-Wall"

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace AlgoSort {

template <typename Arr>
concept SortableArray = requires(Arr a, size_t i) {
        { a[i] };
        { a[i] = a[i] };
    } && std::totally_ordered<
        std::remove_cvref_t<
            decltype(std::declval<Arr>()[0])
        >
    >;
template <typename Arr>
using element_t =
    std::remove_cvref_t<
        decltype(std::declval<Arr>()[0])
    >;
//////////////////////////////////////////////////////
/// \sort a array objects using selection sort algo
/// 
/// time complexity : O(n^2)
/// space complexity: O(1)
/// swaps           : O(n)
///
/// Low To High
///
//////////////////////////////////////////////////////
template <SortableArray Arr>
inline void selection_sort(Arr& arr, const size_t& arr_length) {
    using T = element_t<Arr>;
    
    // i is the index of sorted or the front of unsorted
    // partition, bellow it is the end of the sorted
    for (uint_fast32_t front = 0; front < arr_length - 1; front++) {
        // current known smallest
        uint_fast32_t c_min = front;
        // c_item is the current item
        // find the smallest item on the unsorted partition
        for (uint_fast32_t c_item = front + 1; c_item < arr_length; c_item++) {
            if (arr[c_item] < arr[c_min]) {
                c_min = c_item;
            }
        }
        // now we have the smallest item we then swap it to the
        // front this avoids too much swaps
        const T temp = arr[front];
        arr[front] = arr[c_min];
        arr[c_min] = temp;
    }
}
//////////////////////////////////////////////////////
/// \sort a array objects using bubble sort algo
///
/// time complexity:  O(n^2)
/// space complexity: O(1)
/// swaps           : O(n^2)
///
/// Low To High
///
//////////////////////////////////////////////////////
template <SortableArray Arr>
inline void bubble_sort(Arr& arr, const size_t arr_length) {
    if (arr_length < 2) return;
    using T = element_t<Arr>;
    for (size_t i = 0; i < arr_length - 1; i++) {
        for (size_t x = 0; x < arr_length - i - 1; x++) {
            if (arr[x] > arr[x+1]) {
                const T temp = arr[x];
                arr[x] = arr[x+1];
                arr[x+1] = temp;
            }
        }
    }
}
//////////////////////////////////////////////////////
/// \sort a array objects using bubble sort algo
///
//////////////////////////////////////////////////////
template <SortableArray Arr>
inline void bubble_sort_reverse(Arr& arr, const size_t arr_length) {
    if (arr_length < 2) return;
    using T = element_t<Arr>;
    for (size_t i = 0; i < arr_length - 1; i++) {
        for (size_t x = 0; x < arr_length - i - 1; x++) {
            if (arr[x] < arr[x+1]) {
                const T temp = arr[x];
                arr[x] = arr[x+1];
                arr[x+1] = temp;
            }
        }
    }
}
}; // namespace AlgoSort

