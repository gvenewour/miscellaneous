#pragma once

/** @file
* @brief Struct homework3::impl::Node
*/

namespace homework3 {
    namespace impl {
        /**
         * @brief Нода для кастомного списка @ref homework3::CustomList
         * @tparam T тип значения в вершинах
         */
        template<typename T>
        struct Node {
            T val;
            Node *next{nullptr};
        };
    }
}