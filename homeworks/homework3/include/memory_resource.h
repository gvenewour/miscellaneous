#pragma once

/** @file
* @brief Class @ref homework3::MemoryResource
*/

#include <cstddef>
#include <cstdint>

namespace homework3 {

    /**
    * @brief Основа для работы с любым memory resource
    */
    class MemoryResource {
    public:

        /**
        * @brief Типичный виртуальный деструктор
        */
        virtual ~MemoryResource() = default;

        /**
        * @brief Проверка доступности заданного количества байт для аллокации
        */
        virtual bool available(std::size_t bytes) const = 0;

        /**
        * @brief Функция аллоцирования
        */
        virtual uint8_t* allocate(std::size_t bytes) = 0;

        /**
        * @brief Функция деаллоцирования
        * @note Не используется в рамках ДЗ-03
        */
        virtual void deallocate(void* ptr, std::size_t bytes) = 0;
    };
}