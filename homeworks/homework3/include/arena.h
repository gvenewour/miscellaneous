#pragma once

#include <vector>
#include "memory_resource.h"
//#include <experimental/memory_resource>
#include <iostream>

namespace homework3 {

    //no alignment, simple buffer, nothing interesting here
    class SimpleFixedArena : public MemoryResource {
    public:
        explicit SimpleFixedArena(std::size_t bytes) : _buffer(bytes), _index{0} {
            std::cout << "[arena: " << this << "] constructor for " << bytes << " bytes" << "\n";
        }

        ~SimpleFixedArena() override {
            std::cout << "[arena: " << this << "] destructor " << "\n";
        }

        inline bool available(std::size_t bytes) const override {
            return (_buffer.size() - _index) >= bytes;
        }

        inline uint8_t *allocate(std::size_t bytes) override {
            if (available(bytes)) {
                _index += bytes;

                //std::cout << "[arena: " << this << "] allocated " << bytes << " bytes" << "\n";
                return (&_buffer[_index - bytes]);
            }
            throw std::bad_alloc{};
        }

        void deallocate(void *ptr, std::size_t bytes) override {
            std::cout << "[arena: " << this << "] attempt to deallocate " << bytes << " bytes" << "\n";

            _index = 0;
        };

    private:
        std::vector<uint8_t> _buffer;
        size_t _index;
    };

}