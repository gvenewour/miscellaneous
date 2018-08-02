#pragma once

#include <algorithm>
#include <iostream>

#include "homework2/ip_address.h"

namespace homework2 {

class IpPool {
    public:
        IpPool();

        void sortReverse();

        void print() const;
        void printFilteredBy(const Octet& first) const;
        void printFilteredBy(const Octet& first, const Octet& second) const;
        void printFilteredByAny(const Octet& octet) const;

    private:
        using IpPool_t = std::vector<IpAddress>;

        IpPool_t _pool;
};
}