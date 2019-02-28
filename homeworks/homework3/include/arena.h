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
            LOG(INFO) << strafeLog("[arena: ") << this << "] constructor for " << bytes << " bytes";
        }

        ~SimpleFixedArena() override {
            LOG(INFO) << strafeLog("[arena: ") << this << "] destructor ";
        }

        inline bool available(std::size_t bytes) const override {
            return (_buffer.size() - _index) >= bytes;
        }

        inline uint8_t *allocate(std::size_t bytes) override {
            if (available(bytes)) {
                _index += bytes;

                //VLOG(maxVerbosityLevel) << "[arena: " << this << "] allocated " << bytes << " bytes";
                return (&_buffer[_index - bytes]);
            }
            throw std::bad_alloc{};
        }

        void deallocate(void *ptr, std::size_t bytes) override {
            VLOG(maxVerbosityLevel) << "[arena: " << this << "] attempt to deallocate " << bytes << " bytes";

            _index = 0;
        };

    private:
        std::vector<uint8_t> _buffer;
        size_t _index;
    };

}