#pragma once

/** @file
* @brief Function homework2::bin_id
*/

#include <cstddef>

namespace homework2 {
    /**
    * @brief Решение задачи о вычислении степени двойки через constexpr
    * @note Входит в ДЗ-2, но не относится к решению задачи о фильтрации ip
    * @snippet{.cpp} this constexpr-example
    */

/* [constexpr-example] */
     constexpr size_t bin_id(size_t x, bool inRecurse = false) {
        return (x < 2) ? 0 :
               (inRecurse || ((x & (x - 1)) == 0)) ?
               1 + bin_id(x >> 1, inRecurse) :
               2 + bin_id(x >> 1, true);
    }
/* [constexpr-example] */
}