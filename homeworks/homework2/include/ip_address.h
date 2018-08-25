#pragma once

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <functional>

namespace homework2 {

    using Octet = uint8_t;
    using IpAddress_t = std::vector<Octet>;

    class IpAddress {
        public:
            IpAddress() = default;

            bool fromString(const std::string &str, char delimiter);

            size_t size() const;

            Octet operator [](std::size_t i) const {
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


