#pragma once

/** @file
* @brief Основная часть ДЗ-04: печать адресов на базе чисел, строк и контейнеров std::vector, std::list
*/

#include <iostream>
#include <type_traits>
//#include <experimental/type_traits>

#include <list>
#include <vector>

#include "common.h"

namespace homework4 {

namespace impl {
//    void_t is not available in <experimental/type_traits> for gcc 5.4
//    template<typename T, typename Fake = void>
//    struct is_iterable: std::false_type{};
//
//    template<typename T>
//    struct is_iterable<T, std::void_t<std::enable_if_t<!std::is_same<std::string, T>::value, void>,
//                                                        decltype(std::declval<T>().begin()),
//                                                        decltype(std::declval<T>().end())> : std::true_type{};

    template<typename T>
    struct is_allowed_container: std::false_type{};

    template<typename T>
    struct is_allowed_container<std::vector<T> >: std::integral_constant<bool, is_allowed_type<T>::value>{};

    template<typename T>
    struct is_allowed_container<std::list<T> >: std::integral_constant<bool, is_allowed_type<T>::value>{};

}
    /**
     * @brief Печать адреса на основе числовых типов
    */
    template<typename T>
    typename std::enable_if_t<std::is_integral<typename std::decay<T>::type>::value, std::string>
    print_ip(T&& address) {
        return impl::printBytes(address);
    }

    /**
     * @brief Печать адреса на основе std::string
    */
    template<typename T>
    typename std::enable_if_t<std::is_convertible<typename std::decay<T>::type, std::string>::value, std::string>
    print_ip(T&& address) {
        return address;
    }

    /**
     * @brief Печать адреса на основе контейнеров std::vector и std::list
    */
    template<typename T>
    typename std::enable_if_t<impl::is_allowed_container<T>::value, std::string>
    print_ip(T&& address) {
        bool dot{false};

        constexpr auto container {true};

        std::ostringstream log;

        for (const auto& octet: address) {
            log << (dot ? "." : "");
            dot = true;

            //NOTE: here constexpr if could really help.
            log << impl::printBytes(octet, container);
        }

        return log.str();
    }
}