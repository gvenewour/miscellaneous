/** @file
* @brief Class @ref homework2::IpPool
*/

#include <fstream>
#include <functional>
#include <tuple>
#include "ip_pool.h"


namespace homework2 {
    IpPool::IpPool(std::istream& stream) noexcept{
        _readPool(stream);
    }

    IpPool::IpPool(const fs::path& path)
    {
        if (fs::is_regular_file(path)) {
            std::ifstream file{path};
            _readPool(file);
        } else
            throw std::runtime_error("failed to open file ");
    }

    void IpPool::_readPool(std::istream &stream) {
        std::string ip{}, skip{};
        IpAddress address{};
        while (stream >> ip) {
            if (address.fromString(ip, '.')) {
                _pool.emplace_back(address);
            }
            std::getline(stream, skip);
        }
    }

    void IpPool::sortReverse() {
        std::sort(_pool.begin(), _pool.end(), std::greater<>());
    }

    void IpPool::print() const {
        for (const auto& address: _pool) {
            std::cout << address << "\n";
        }
    }

    void IpPool::printBy(const Octet &first) const {
        struct comparator {
            bool operator()(const IpAddress &address, Octet first) const {
                return address[0] > first;
            }

            bool operator()(Octet first, const IpAddress &address) const {
                return first > address[0];
            }
        };

        //NOTE: At most log2(last - first) + O(1) comparisons
        const auto range = std::equal_range(_pool.cbegin(), _pool.cend(), first, comparator{});

        for (auto address = range.first; address != range.second; ++address) {
            std::cout << *address << "\n";
        }
    }

    void IpPool::printBy(const Octet &first, const Octet &second) const {
        struct comparator {
            bool operator()(const IpAddress &address, std::tuple<Octet, Octet> octets) const {
                Octet first = std::get<0>(octets);
                Octet second = std::get<1>(octets);

                return (address[0] > first) ||
                       ((address[0] == first) && (address[1] > second));
            }

            bool operator()(std::tuple<Octet, Octet> octets, const IpAddress &address) const {
                Octet first = std::get<0>(octets);
                Octet second = std::get<1>(octets);

                return (first > address[0]) ||
                       ((first == address[0]) && (second > address[1]));
            }
        };

        //NOTE: At most log2(last - first) + O(1) comparisons
        const auto range = std::equal_range(_pool.cbegin(), _pool.cend(), std::make_tuple(first, second), comparator{});

        for (auto address = range.first; address != range.second; ++address) {
            std::cout << *address << "\n";
        }
    }

    void IpPool::printByAny(const Octet &octet) const {
        //NOTE: linear search is a suboptimal solution - O(n) comparisons. what is the best one?

        for (const auto &address: _pool) {
            if (std::any_of(address.cbegin(), address.cend(), [octet](Octet i){ return (i == octet); })) {
                std::cout << address << "\n";
            }
        }
    }
}