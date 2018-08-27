#pragma once

#include <memory>
#include "arena.h"

namespace homework3 {

    template<typename T, std::size_t maxCount>
    class LinearAllocator {
    public:
        using value_type = T;
        //pointer types are inferred by std::allocator_traits<>

        template<class U>
        struct rebind {
            using other = LinearAllocator<U, maxCount>;
        };

        auto allocate(std::size_t n) {
            if (!_arena) {
                _arena.reset(new SimpleFixedArena{maxCount * sizeof(T)});
            }

            const std::size_t bytes = n * sizeof(T);

            if (_arena->available(bytes)) {
                return reinterpret_cast<T *>(_arena->allocate(bytes));
            }

            throw std::bad_alloc{};
        }

        void deallocate(T *p, std::size_t n) {}

        LinearAllocator() = default;
//        LinearAllocator(const LinearAllocator&) = default;

        template<typename U>
        explicit LinearAllocator(const LinearAllocator<U, maxCount> &) noexcept {}

    private:
        std::shared_ptr<MemoryResource> _arena;
    };

    //Objects allocated from one instance should not be safely freed on another
    //TODO: test on multiple node containers!

    template<typename T, typename U, std::size_t maxCount>
    inline bool operator==(const LinearAllocator<T, maxCount> &, const LinearAllocator<U, maxCount> &) {
        return false;
    }

    template<typename T, typename U, std::size_t maxCount>
    inline bool operator!=(const LinearAllocator<T, maxCount> &a, const LinearAllocator<U, maxCount> &b) {
        return !(a == b);
    }
}