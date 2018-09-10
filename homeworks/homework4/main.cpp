#include <iostream>
#include <list>
#include <vector>

#include <experimental/type_traits>


template<typename T>
struct is_container: std::false_type{};

template<typename T>
struct is_container<std::vector<T> >: std::true_type{};

template<typename T>
struct is_container<std::list<T> >: std::true_type{};

template<typename T>
typename std::enable_if_t<is_container<T>::value, void> print_ip(T address) {
    std::cout << "container" << "\n";
}

template<typename T>
typename std::enable_if_t<std::is_integral<T>::value, void> print_ip(T address) {
    std::cout << "bytes" << "\n";
}

template<typename T>
typename std::enable_if_t<std::is_same<std::string, T>::value, void> print_ip(T address) {
    std::cout << "string" << "\n";
}


int main () {
    int val1 {0};
    print_ip(val1);

    std::string val2{"ololo"};
    print_ip(val2);

    std::vector<int> val3 {1, 2, 3, 4};
    print_ip(val3);

    return 0;
}