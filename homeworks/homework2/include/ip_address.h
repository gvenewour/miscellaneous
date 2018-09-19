#pragma once

/** @file
* @brief Class @ref homework2::IpAddress
*/

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

namespace homework2 {

    /**
     * @brief Тип октета в адресе
     */
    using Octet = uint8_t;

    using IpAddress_t = std::vector<Octet>;

     /**
     * @brief Класс, представляющий ip адрес
     * @see @ref homework2::IpPool, homework2::Octet
     */
class IpAddress {
    public:

        /**
        * @brief Конструктор пустого адреса
        */
        IpAddress() = default;

        /**
        * @brief  Инициализирует адрес из токенов в строке.
        * @param[in] str исходная строка
        * @param[in] delimiter разделитель для токенизации строки
        */
        bool fromString(const std::string &str, char delimiter);

        /**
        * @brief Возвращает количество октетов в адресе
        */
        size_t size() const;

        const Octet& operator [](std::size_t i) const {
            return _address[i];
        }

        friend bool operator< (const IpAddress& lhs, const IpAddress& rhs) {
            return (lhs._address < rhs._address);
        }

        friend bool operator> (const IpAddress& lhs, const IpAddress& rhs) {
            return (lhs._address > rhs._address);
        }

        IpAddress_t::const_iterator cbegin() const {return _address.cbegin();}
        IpAddress_t::const_iterator cend() const {return _address.cend();}

    private:
        bool _isValid(const IpAddress_t& address) const;
        IpAddress_t _address;
};

    std::ostream& operator<<(std::ostream& str, const IpAddress& address);
}