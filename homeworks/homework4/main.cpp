#include <iostream>
#include <climits>
#include <limits>
#include <list>
#include <vector>

#include <experimental/type_traits>

template<typename T>
void printBytes(T address) {
    static_assert(std::is_integral<T>::value, "we need a numeric value for bitwise operations");

    using Unsigned = std::make_unsigned_t<T>;
    const auto value = static_cast<Unsigned>(address);

    constexpr auto MASK {0xFFU};
    constexpr auto NBITS = std::numeric_limits<Unsigned>::digits;

    auto shift{0};
    auto rotatedValue{0};
    auto octet{0};

    for (uint8_t i = 1; i <= sizeof(Unsigned); ++i) {
        shift = CHAR_BIT*i;
        rotatedValue = (value << shift) | (value >> (NBITS - shift));
        octet = rotatedValue & MASK;

        std::cout << octet;

        std::cout << (i < sizeof(Unsigned) ? "." : "");
    }
}

template<typename T>
struct is_container: std::false_type{};

template<typename T>
struct is_container<std::vector<T> >: std::true_type{};

template<typename T>
struct is_container<std::list<T> >: std::true_type{};

template<typename T>
typename std::enable_if_t<is_container<T>::value, void> print_ip(T address) {
    bool dot{false};
    for (const auto& octet: address) {
        std::cout << (dot ? "." : "");
        dot = true;

        printBytes(octet);
    }
    std::cout << "\n";
}

template<typename T>
typename std::enable_if_t<std::is_integral<T>::value, void> print_ip(T address) {
    printBytes(address);
    std::cout << "\n";
}

template<typename T>
typename std::enable_if_t<std::is_same<std::string, T>::value, void> print_ip(T address) {
    std::cout << address << "\n";
}

int main () {
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(std::string{"trololololo"});
    print_ip(std::vector<char>{-1, -2, -3, -4});
    //print_ip(std::vector<std::string>{"ololo"});
    print_ip(std::list<int>{1, 2, 3, 4});

    return 0;
}