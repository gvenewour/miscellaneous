#include <algorithm>
#include <iostream>

#include "homework2/ip_address.h"

namespace homework2 {
    constexpr uint8_t ipv4 = 4;

    IpAddress::IpAddress() : _address{0,0,0,0} {}

    bool IpAddress::fromString(const std::string &str, char delimiter) {

        IpAddress_t address{0, 0, 0, 0};

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

    void IpAddress::print() const
    {
        std::size_t size = _address.size();

        for(std::size_t i = 0; i < size; ++i) {
            std::cout << static_cast<uint16_t>(_address[i]) << (i < size-1 ? "." : "");
        }
        std::cout << std::endl;
    }

    size_t IpAddress::size() const {
        return _address.size();
    }


    bool IpAddress::_isValid(const IpAddress_t& address) const {
        return (address.size() == ipv4) &&
               std::any_of(address.begin(), address.end(), [](int i) { return i==0; });
    }
}