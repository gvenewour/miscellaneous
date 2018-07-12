#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <algorithm>
#include <tuple>

using Octet = std::uint8_t;
using IpAddress = std::vector<Octet>;
using IpPool = std::vector<IpAddress>;


IpAddress tokenize(const std::string &str, char delimiter)
{
    IpAddress r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimiter);
    while(stop != std::string::npos)
    {
        r.emplace_back(static_cast<Octet>(std::strtoul(str.substr(start, stop - start).c_str(),
                                                         nullptr,
                                                         10)));

        start = stop + 1;
        stop = str.find_first_of(delimiter, start);
    }

    r.emplace_back(static_cast<Octet>(std::strtoul(str.substr(start).c_str(),
                                                     nullptr,
                                                     10)));

    return r;
}


void print(const IpAddress& address) {
   std::size_t size = address.size();

   for(std::size_t i = 0; i < size; ++i) {
       std::cout << static_cast<uint16_t>(address[i]) << (i < size-1 ? "." : "");
   }
   std::cout << std::endl;
}

void reverseSortByOctets(IpPool& pool) {
    std::sort(std::begin(pool), std::end(pool), [](const IpAddress& a, const IpAddress& b) {
                                                   std::size_t size = (a.size() > b.size()) ? b.size() : a.size();
                                                   bool before {false};

                                                   for (std::size_t i = 0; i < size; ++i) {
                                                      if (a[i] != b[i]) {
                                                        before = (a[i] > b[i]);
                                                        break;
                                                      }
                                                   }

                                                   return before;
                                                });
}

void filter(const IpPool& pool, Octet first) {
    struct comparator {
        bool operator()(const IpAddress& address, Octet first) const {
            return address[0] > first;
        }

        bool operator()(Octet first, const IpAddress& address) const {
            return first > address[0];
        }
    };

    //At most log2(last - first) + O(1) comparisons
    auto range = std::equal_range(std::begin(pool), std::end(pool), first, comparator{});

    for (auto address = range.first; address != range.second; ++address) {
        print(*address);
    }
}

void filter(const IpPool& pool, Octet first, Octet second) {
    struct comparator {
        bool operator()(const IpAddress& address, std::tuple<Octet, Octet> octets) const {
            Octet first = std::get<0>(octets);
            Octet second = std::get<1>(octets);

            return (address[0] > first) ||
                   ((address[0] == first) && (address[1] > second));
        }

        bool operator()(std::tuple<Octet, Octet> octets, const IpAddress& address) const {
            Octet first = std::get<0>(octets);
            Octet second = std::get<1>(octets);

            return (first > address[0]) ||
                   ((first == address[0]) && (second > address[1]));
        }
    };

    //At most log2(last - first) + O(1) comparisons
    auto range = std::equal_range(std::begin(pool), std::end(pool), std::make_tuple(first, second), comparator{});

    for (auto address = range.first; address != range.second; ++address) {
        print(*address);
    }
}

void filter_any(const IpPool& pool, Octet octet) {
    //? linear search is the suboptimal solution - O(n) comparisons. what is the best one?

    for (const auto& address : pool) {
        if ((address[0] == octet) || address[1] == octet || address[2] == octet || address[3] == octet) {
            print(address);
        }
    }
}

int ip_filter()
{
    try {
        IpPool ip_pool;

        std::string ip, skip;

        while (std::cin >> ip) {
            ip_pool.emplace_back(tokenize(ip, '.'));
            std::getline(std::cin, skip);
        }

        reverseSortByOctets(ip_pool);

        for (const auto& address: ip_pool) {
            print(address);
        }

        filter(ip_pool, 1);
        filter(ip_pool, 46, 70);
        filter_any(ip_pool, 46);
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
