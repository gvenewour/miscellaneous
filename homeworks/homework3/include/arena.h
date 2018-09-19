#pragma once

/** @file
* @brief Class @ref homework3::SimpleFixedArena
*/

#include <vector>
#include "memory_resource.h"
//#include <experimental/memory_resource>
#include <iostream>


namespace homework3 {

    /**
     * @brief Класс, представляющий арену фиксированного размера
     * @note Возможность увеличения объема доступной памяти не предусмотрена
     * @see @ref homework3::LinearStatefulAllocator
     */
    class SimpleFixedArena : public MemoryResource {
    public:

        /**
         * @brief Конструктор.
         * @param bytes количество байт для создания буфера фиксированного размера
         */
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