#include <cstdint>

#include <iostream>

#include "parser.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }

    std::cout << argv[1] << std::endl;

    const uint64_t chunksMaxDefault = strtoul(argv[1], nullptr, 10);

    homework7::Parser parser{chunksMaxDefault};


    parser.start();

    return 0;
}