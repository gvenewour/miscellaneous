#pragma once

/** @file
* @brief Class homework3::CustomList
*/

#include <initializer_list>
#include <iterator>
#include <memory>
#include <list>

#include "custom_list_node.h"
#include "custom_list_iterator.h"

namespace homework3 {

    /**
     * @brief Кастомная реализация нодового контейнера, реализующего список.
     * Поддерживает работу с @ref homework3::LinearStatefulAllocator
     * @tparam T тип элемента контейнера
     * @tparam A тип аллокатора
     */
    template<typename T, typename A = std::allocator<T> >
    class CustomList {
        public:

            using node_type = impl::Node<T>;
            using iterator = impl::CustomIterator<T>;   //or we could define iterators as member classes
            using const_iterator = impl::CustomIterator<T>;
            using traits = std::allocator_traits<A>;
            using rebound_alloc_type = typename std::allocator_traits<A>::template rebind_alloc<node_type> ;

            CustomList() : _reboundAllocator(), _root{nullptr}, _last{nullptr}{};
            CustomList(std::initializer_list<T> list);

            CustomList(const CustomList&) = delete;
            CustomList(CustomList&&) = delete;
            CustomList& operator=(const CustomList&) = delete;
            CustomList& operator=(CustomList&&) = delete;

            void insert(T val);

            iterator begin() {
                return iterator(_root);
            }

            iterator end() {
                return iterator(nullptr);
            }

//          const_iterator begin() const
//          {
//              return const_iterator(_root);
//          }
//
//          const_iterator end() const
//          {
//              return const_iterator(_last);
//          }
        private:
            void _insert(node_type** node, T val);
//            A _allocator;
            rebound_alloc_type _reboundAllocator;
            node_type *_root, *_last;
    };

    #include "custom_list.tpp"
}
