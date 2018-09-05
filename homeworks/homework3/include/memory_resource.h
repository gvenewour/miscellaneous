#pragma once

#include <cstddef>
#include <cstdint>

namespace homework3 {
    class MemoryResource {
    public:
        virtual ~MemoryResource() = default;

        virtual bool available(std::size_t bytes) const = 0;

        virtual uint8_t* allocate(std::size_t bytes) = 0;
        virtual void deallocate(void* ptr, std::size_t bytes) = 0;
    };
}