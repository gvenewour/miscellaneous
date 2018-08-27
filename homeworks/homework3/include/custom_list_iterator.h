#pragma once

#include <iterator>
#include "custom_list_node.h"

namespace homework3 {
    namespace impl {
        template<typename T> /*, bool isConst = false>*/ //NOTE: can implement const_iterators without duplicating code
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

            //pre-increment
            CustomIterator& operator++() {
                if (_current) {
                    _current = _current->next;
                } else {
                    //FIXME: should throw!
                }
                return *this;
            }

            //post-increment
            CustomIterator operator++(int) {
                CustomIterator tmp = *this;

                if (_current) {
                    _current = _current->next;
                } else {
                    //FIXME: should throw!
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

