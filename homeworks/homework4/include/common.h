#pragma once

#include <climits>
#include <limits>
#include <type_traits>

#include <iostream>
#include <string>

/** \addtogroup homework4
 *  @{
 */

namespace homework4 {
    template<typename T>
    struct is_allowed_type : std::integral_constant < bool,
                                                      std::is_integral<T>::value ||
                                                      std::is_same<T, std::string > ::value > {};

    template<typename T>
    void _printBytes(T address) {
        static_assert(std::is_integral<T>::value, "we need a numeric value for bitwise operations");

        using unsigned_t = std::make_unsigned_t<T>;
        const auto value = static_cast<unsigned_t>(address);

        constexpr auto MASK {0xFFU};
        constexpr auto NBITS = std::numeric_limits<unsigned_t>::digits;

        auto shift{0};
        auto rotatedValue{0};
        auto octet{0};

        for (uint8_t i = 1; i <= sizeof(unsigned_t); ++i) {
            shift = CHAR_BIT*i;
            rotatedValue = (value << shift) | (value >> (NBITS - shift));
            octet = rotatedValue & MASK;

            std::cout << octet;

            std::cout << (i < sizeof(unsigned_t) ? "." : "");
        }
    }
}

/** @}*/