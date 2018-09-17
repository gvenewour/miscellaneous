#pragma once

/** @file
* @brief Struct homework3::impl::Node
*/

namespace homework3 {
    namespace impl {
        /**
         * @tparam T тип значения в вершинах
         */
        template<typename T>
        struct Node {
            T val;
            Node *next{nullptr};
        };
    }
}