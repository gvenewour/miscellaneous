#pragma once

#include <vector>
#include "memory_resource.h"
//#include <experimental/memory_resource>

namespace homework3 {

    //no alignment, simple buffer, nothing interesting here
    class SimpleFixedArena : public MemoryResource {
    public:
        explicit SimpleFixedArena(std::size_t bytes) : _buffer(bytes), _index{0} {}

        bool available(std::size_t bytes) const override {
            return (_buffer.size() - _index) >= bytes;
        }

        uint8_t *allocate(std::size_t bytes) override {
            if (available(bytes)) {
                _index += bytes;
                return (&_buffer[_index - bytes]);
            }
            throw std::bad_alloc{};
        }

        void deallocate(std::size_t bytes) override {}

    private:
        std::vector<uint8_t> _buffer;
        size_t _index;
    };

}