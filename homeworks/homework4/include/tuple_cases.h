#pragma once

/** @file
* @brief Опциональная часть ДЗ-04. Печать адресов на базе кортежей
*/

#include <iostream>

#include <string>
#include <tuple>

#include "common.h"
#include "base_cases.h"


namespace homework4 {
    namespace impl {
        //https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat

        template<class T, std::size_t N>
        struct TuplePrinter {
            static std::string print(const T& t) {
                constexpr auto raw {true};
                return TuplePrinter<T, N-1>::print(t) + "." + printBytes(std::get<N-1>(t), raw);
            }
        };

        template<class T>
        struct TuplePrinter<T, 1> {
            static std::string print(const T& t) {
                constexpr auto raw {true};
                return printBytes(std::get<0>(t), raw);
            }
        };

        template<class... Args>
        std::string print(const std::tuple<Args...>& t) {
            return TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
        }

    template<typename T, std::size_t N = std::tuple_size<T>::value>
    struct allowed_tuple_types: std::integral_constant<bool,
                                                       is_allowed_type<std::tuple_element_t<N-1, T>>::value &&
                                                       allowed_tuple_types<T, N-1>::value>{};

    template<typename T>
    struct allowed_tuple_types<T, 1>:
           std::integral_constant<bool, is_allowed_type<std::tuple_element_t<0, T> >::value> {};
    }

    /**
     * @brief Печать адреса на основе кортежей
     */
    template<typename T>
    typename std::enable_if_t<impl::allowed_tuple_types<T, std::tuple_size<T>::value>::value, std::string>
    print_ip(T address) {
        return impl::print(address);
    }
}