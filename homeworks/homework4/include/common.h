#pragma once

/** @file
* @brief Побайтовый вывод числа, проверка типа на допустимость
*/

#include <climits>
#include <limits>
#include <type_traits>

#include <iostream>
#include <string>
#include <sstream>


namespace homework4 {

namespace impl {
    template<typename T>
    struct is_allowed_type : std::integral_constant<bool,
                                                    std::is_integral<T>::value ||
                                                    std::is_same<T, std::string>::value> {
    };

    template<typename T>
    std::enable_if_t<std::is_convertible<typename std::decay<T>::type, std::string>::value, std::string>
    printBytes(T address, bool raw = false) {
        return address;
    }

    template<typename T>
    std::enable_if_t<std::is_integral<typename std::decay<T>::type>::value, std::string>
    printBytes(T address, bool raw = false) {
        static_assert(std::is_integral<T>::value, "we need a numeric value for bitwise operations");

        using unsigned_t = std::make_unsigned_t<T>;
        const auto value = static_cast<unsigned_t>(address);

        constexpr auto MASK{0xFFU};
        constexpr auto NBITS = std::numeric_limits<unsigned_t>::digits;

        auto shift{0};
        auto rotatedValue{0};
        auto octet{0};

        std::ostringstream log;

        if (raw) {
            log << +value;
        } else {
            for (uint8_t i = 1; i <= sizeof(unsigned_t); ++i) {
                shift = CHAR_BIT * i;
                rotatedValue = (value << shift) | (value >> (NBITS - shift));
                octet = rotatedValue & MASK;

                log << octet;

                log << (i < sizeof(unsigned_t) ? "." : "");
            }
        }

        return log.str();
    }
}
}