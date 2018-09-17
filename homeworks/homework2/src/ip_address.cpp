#include <algorithm>
#include <iostream>

/** @file
* @brief Class @ref homework2::IpAddress
*/

#include "ip_address.h"

namespace homework2 {
    constexpr uint8_t ipv4 = 4;

    bool IpAddress::fromString(const std::string &str, char delimiter) {

        IpAddress_t address{};

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(delimiter);

        const char* token{nullptr};
        while(stop != std::string::npos)
        {
            token = str.substr(start, stop - start).c_str();
            address.emplace_back(std::strtoul(token, nullptr, 10));

            start = stop + 1;
            stop = str.find_first_of(delimiter, start);
        }

        token = str.substr(start).c_str();
        address.emplace_back(std::strtoul(token, nullptr, 10));

        bool result = _isValid(address);
        if (result) {
            _address = address;
        }
        return result;
    }

    size_t IpAddress::size() const {
        return _address.size();
    }

    bool IpAddress::_isValid(const IpAddress_t& address) const {
        return ((address.size() == ipv4)
                /* && std::all_of(address.begin(), address.end(), [](Octet i) { return ????; })*/);
    }

    std::ostream& operator<<(std::ostream& str, const IpAddress& address) {
        const std::size_t size = address.size();
        std::ostringstream concatenate{};
        for(std::size_t i = 0; i < size; ++i) {
            concatenate << static_cast<uint16_t>(address[i]) << (i < size-1 ? "." : "");
        }
        return str << concatenate.str();
    }
}