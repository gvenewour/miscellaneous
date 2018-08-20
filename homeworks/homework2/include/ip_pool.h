#pragma once

#include <algorithm>
#include <iostream>

#include <experimental/filesystem>
#include "ip_address.h"

namespace fs = std::experimental::filesystem;

namespace homework2 {

class IpPool {
    public:
        IpPool() noexcept = default;
        IpPool(std::istream& stream) noexcept;
        IpPool(const fs::path& path);

        void sortReverse();

        std::size_t size() const { return _pool.size();}
        void print() const;
        void printFilteredBy(const Octet& first) const;
        void printFilteredBy(const Octet& first, const Octet& second) const;
        void printFilteredByAny(const Octet& octet) const;

    private:
        using IpPool_t = std::vector<IpAddress>;

        void _readPool(std::istream& stream);

        IpPool_t _pool;
};
}