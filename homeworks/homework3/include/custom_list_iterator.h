#pragma once

/** @file
* @brief Class @ref homework3::impl::CustomIterator
*/

#include <iterator>
#include "custom_list_node.h"

namespace homework3 {

    namespace impl {

        /** @brief Class homework3::impl::CustomIterator
         * @note Можно запилить константность итераторов без дублирования кода
         * @see @ref homework3::impl::Node, homework3::CustomList
         */
        //NOTE: const_iterators can be implemented without duplicating code
        template<typename T> /*, bool isConst = false>*/
        class CustomIterator {
        public:
            using value_type = T;
            using reference  = T&;
            using pointer    = T*;
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;

            CustomIterator(): _current{nullptr}{};

            explicit CustomIterator(Node<T> *node) : _current{node} {};

            reference operator*() const { return _current->val; };

            pointer operator->() const {
                return addressof(operator*());
            }

            CustomIterator& operator++() {
                if (_current) {
                    _current = _current->next;
                }

                return *this;
            }

            CustomIterator operator++(int) {
                CustomIterator tmp = *this;

                if (_current) {
                    _current = _current->next;
                }

                return tmp;
            }

            bool operator==(const CustomIterator &rhs) { return _current == rhs._current; }
            bool operator!=(const CustomIterator &rhs) { return _current != rhs._current; }

        private:
            Node<T> *_current;
        };
    }
}