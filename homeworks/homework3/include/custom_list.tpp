#include "custom_list.h"

/** @file
* @brief Class homework3::CustomList
*/

template<typename T, typename A>
CustomList<T,A>::CustomList(std::initializer_list<T> list) : CustomList(){
    for (auto val: list) {
        insert(val);
    }
}

template<typename T, typename A>
void CustomList<T, A>::insert(T val) {
    auto current = _root? &_last : &_root;
    _insert(current, val);
}

template<typename T, typename A>
void CustomList<T, A>::_insert(node_type **node, T val) {
    if (*node == nullptr) {
        node_type* tmp =  std::allocator_traits<rebound_alloc_type>::allocate(_reboundAllocator, 1);
        tmp->val = val;
        tmp->next = nullptr;
        *node = tmp;

        if (!_last) {
            _last = _root;
        }
    } else {
        _insert(&(*node)->next, val);
    }
}