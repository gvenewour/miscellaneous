#pragma once

/** @file
* @brief Class homework3::LinearStatefulAllocator
*/

#include <memory>
#include "arena.h"

#include <iostream>

namespace homework3 {

    /**
    * @brief Кастомный аллокатор. Поддерживает нодовые контейнеры
    */
    template<typename T, std::size_t maxCount>
    class LinearStatefulAllocator {
    public:
        using value_type = T;
        //pointer types are inferred by std::allocator_traits<>

        using propagate_value = std::false_type;

        using propagate_on_container_copy_assignment = propagate_value;
        using propagate_on_container_move_assignment = propagate_value;
        using propagate_on_container_swap_assignment = propagate_value;

        //using is_always_equal = std::false_type;

        static LinearStatefulAllocator select_on_container_copy_construction(const LinearStatefulAllocator& rhs) {
            VLOG(maxVerbosityLevel) << "select_on_container_copy_construction";

            return LinearStatefulAllocator();
        }

        template<class U>
        struct rebind {
            using other = LinearStatefulAllocator<U, maxCount>;
        };

        auto allocate(std::size_t n) {
            if (!_arena) {
                _arena.reset(new SimpleFixedArena{maxCount * sizeof(T)});
            }

            const std::size_t bytes = n * sizeof(T);
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] allocate " << bytes << " bytes from arena " << _arena.get();
            return reinterpret_cast<T *>(_arena->allocate(bytes));
        }

        void deallocate(T *p, std::size_t n) {
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] deallocation request for arena " << _arena.get();

            //if (_arena) { //comparison for gcc<5.5
            //    _arena->deallocate(p, n*sizeof(T));
            //}
        }

        template<typename U>
        explicit LinearStatefulAllocator(const LinearStatefulAllocator<U, maxCount> &) noexcept {}

        LinearStatefulAllocator() noexcept{
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] default constructor, sizeof(T): " << sizeof(T);
        };

        ~LinearStatefulAllocator() noexcept {
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] destructor, sizeof(T): " << sizeof(T)
                                    << ", arena: " << _arena.get();
        };

        LinearStatefulAllocator(const LinearStatefulAllocator& rhs){
            VLOG(maxVerbosityLevel) << "[allocator: " << this       << "] copy constructor call, original allocator: "
                                    << &rhs           <<", sizeof(T): " << sizeof(T)  << " , arena: " << _arena.get();
        };

        LinearStatefulAllocator(LinearStatefulAllocator&& rhs): _arena(std::move(rhs._arena)){
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] move constructor call, original allocator: " << &rhs
                                    <<", sizeof(T): " << sizeof(T) << " , arena: " << _arena.get();
        };

        LinearStatefulAllocator & operator = (const LinearStatefulAllocator & rhs) = delete;
        LinearStatefulAllocator & operator = (LinearStatefulAllocator &&) = delete;

        template <typename U>
        friend bool operator==(const LinearStatefulAllocator<T, maxCount> &a, const LinearStatefulAllocator<U, maxCount> &b) {
            return false;
        }

        template <typename U>
        friend bool operator!=(const LinearStatefulAllocator<T, maxCount> &a, const LinearStatefulAllocator<U, maxCount> &b) {
            return !(a == b);
        }

        template<typename U, typename ...Args>
        void construct(U *p, Args &&...args) {
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] construct called for an object with address " << p
                                    << " (arena: " << _arena.get() << ")";

            new(p) U(std::forward<Args>(args)...);
        }

        void destroy(T *p) {
            VLOG(maxVerbosityLevel) << "[allocator: " << this << "] destroy called for an object with address " << p
                                    << " (arena: " << _arena.get() << ")\n";
            p->~T();
        }

    private:
        std::unique_ptr<MemoryResource> _arena;
    };
}