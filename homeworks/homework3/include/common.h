#pragma once

/** @file
* @brief Functions @ref homework3::factorial(), homework3::fill(), homework3::print()
*/

#include <cstdint>
#include <iostream>
#include <sstream>

#include "easylogging++.h"

namespace homework3 {

    constexpr auto maxVerbosityLevel = 9;

    /**
     * @brief Тип ключа в нодовых контейнерах ДЗ-3
    */
    using Key = int;

    /**
     * @brief Тип значения в нодовых контейнерах ДЗ-3
    */
    using Val = int;

    /**
     * @brief Верхняя граница количества элементов в контейнерах ДЗ-3
    */
    constexpr uint8_t maxCount{10};

    /**
     * @brief Тривиальная функция вычисления факториала
    */
    //tgamma = (n-1)!
    constexpr int factorial(int n) {
        return n > 0 ? n * factorial(n - 1) : 1;
    }

    /**
     * @brief Заполняет контейнер map ключами от 0 до @ref homework3::maxCount и значениями @ref homework3::factorial()
    */
    template<typename T>
    void fill(T &map) {
        for (auto i = 0; i < maxCount; ++i) {
            map[i] = factorial(i);
        }
    }

    /**
     * @brief Выводит элементы контейнера map в формате [ключ значение]
    */
    template<typename T>
    std::string print(T &map) {
        std::ostringstream log;
        for (const auto &it : map) {
            log << "[" << it.first << " " << it.second << "] ";
        }
        return log.str();
    }

    inline std::string strafeLog(const std::string& str) {
        std::ostringstream log;
        log << "    " << str;
        return log.str();
    }

}