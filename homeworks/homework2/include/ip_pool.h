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
        explicit IpPool(std::istream& stream) noexcept;
        explicit IpPool(const fs::path& path);

        void sortReverse();

        std::size_t size() const { return _pool.size();}
        void print() const;
        void printBy(const Octet& first) const;
        void printBy(const Octet& first, const Octet& second) const;
        void printByAny(const Octet& octet) const;

    private:
        using IpPool_t = std::vector<IpAddress>;

        void _readPool(std::istream& stream);

        IpPool_t _pool;
};
}