#pragma once

/** @file
* @brief Class @ref homework2::IpPool
*/

#include <algorithm>
#include <iostream>

#include <experimental/filesystem>
#include "ip_address.h"

namespace fs = std::experimental::filesystem;

namespace homework2 {

    /**
     * @brief Класс, представляющий пул адресов
     * @see @ref homework2::IpAddress, homework2::Octet
     */
class IpPool {
    public:

        /**
        * @brief Конструктор по умолчанию; создает пустой пул
        */
        IpPool() noexcept = default;

        /**
        * @brief Конструктор, инициализирующий элементы пула из потока
        */

        explicit IpPool(std::istream& stream) noexcept;

        /**
         * @brief Конструктор, позволяющий загрузить пул адресов напрямую из файла
         * @note Использует std::experimental::filesystem
        */
        explicit IpPool(const fs::path& path);

        /**
        * @brief Обратная сортировка по октетам
        */
        void sortReverse();

        /**
        * @brief Возвращает размер пула адресов
        */
        std::size_t size() const { return _pool.size();}

        /**
        * @brief Вывод всех адресов из пула
        */
        void print() const;

        /**
        * @brief Вывод адресов из пула по значению первого октета
        *  @note Решение через equal_range. Дает log2(last - first) + O(1) сравнений
        */
        void printBy(const Octet& first) const;

        /** @brief Вывод адресов из пула по значениям первого и второго октетов
         *  @note Решение через equal_range. Дает log2(last - first) + O(1) сравнений
        */
        void printBy(const Octet& first, const Octet& second) const;

        /** @brief Вывод адресов из пула по значению любого из октетов
        *  @note Решение через линейный поиск. Дает O(n) сравнений. Можно ли улучшить?
        */
        void printByAny(const Octet& octet) const;

    private:
        using IpPool_t = std::vector<IpAddress>;

        void _readPool(std::istream& stream);

        IpPool_t _pool;
    };
}