#include <cstdint>
#include <string>
#include <tuple>
#include <vector>
#include <functional>


namespace homework2 {

using Octet = uint8_t;
using IpAddress_t = std::vector<Octet>;

class IpAddress {
    public:
        IpAddress();

        bool fromString(const std::string &str, char delimiter);

        void print() const;
        size_t size() const;

        Octet operator [](int i) const {
            return _address[i];
        }

        friend bool operator< (const IpAddress& lhs, const IpAddress& rhs)
        {
            return (lhs._address < rhs._address);
        }

        friend bool operator> (const IpAddress& lhs, const IpAddress& rhs)
        {
            return (lhs._address > rhs._address);
        }

    private:
        bool _isValid(const IpAddress_t& address) const;
        IpAddress_t _address;
};
}


