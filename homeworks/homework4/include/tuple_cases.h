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
            static void print(const T& t) {
                TuplePrinter<T, N-1>::print(t);
                std::cout << ".";
                print_ip(std::get<N-1>(t), false);
            }
        };

        template<class T>
        struct TuplePrinter<T, 1> {
            static void print(const T& t) {
                print_ip(std::get<0>(t), false);
            }
        };

        template<class... Args>
        void print(const std::tuple<Args...>& t) {
            TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
            std::cout << "\n";
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
    typename std::enable_if_t<impl::allowed_tuple_types<T, std::tuple_size<T>::value>::value, void>
    print_ip(T address) {
        impl::print(address);
    }
}