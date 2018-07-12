#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>
#include <iomanip>

void task_1001() {
    std::vector<double> numbers;

    std::copy(std::istream_iterator<unsigned long long>(std::cin),
              std::istream_iterator<unsigned long long>(),
              std::back_inserter(numbers));

    std::cout << std::fixed << std::setprecision(4);

    for (auto i = numbers.rbegin(); i != numbers.rend(); ++i) {
        std::cout << std::sqrt(*i) << std::endl;
    }
}

void task_1264() {
   unsigned short n{0}, m{0};

   std::cin >> n >> m;

   std::cout << n*(m + 1) << std::endl;
}

void task_1293() {
   unsigned short N{0}, A{0}, B{0};
   std::cin >> N >> A >> B;
   std::cout << 2*N*A*B << std::endl;
}

void task_1409() {
   unsigned short harry {0}, larry {0};

   std::cin >> harry >> larry;
   std::cout << larry - 1 << " " << harry - 1 << std::endl;

}

void task_1785() {
   unsigned short number;
   std::cin >> number;

   const char* name = (number >= 1   && number <= 4)  ? "few"    :
                      (number >= 5   && number <= 9)  ? "several":
                      (number >= 10  && number <= 19) ? "pack"   :
                      (number >= 20  && number <= 49) ? "lots"   :
                      (number >= 50  && number <= 99) ? "horde"  :
                      (number >= 100 && number <= 249)? "throng" :
                      (number >= 250 && number <= 499)? "swarm"  :
                      (number >= 500 && number <= 999)? "zounds" :
                      "legion";

   std::cout << name << std::endl;
}

void task_1787() {
    unsigned short k{0}, n{0}, left{0};
    std::cin >> k >> n;

    std::vector<unsigned short> cars;

    std::copy(std::istream_iterator<unsigned short>(std::cin),
              std::istream_iterator<unsigned short>(),
              std::back_inserter(cars));

    for (uint16_t i = 0; i < n; ++i) {
        left = (left + cars[i] - k > 0)? left + cars[i] - k : 0;
    }

    std::cout << left << std::endl;
}

void task_1788() {
   unsigned int code1{0}, code2{0};

   std::cin >> code1 >> code2;

   //code1 should be even, code2 should be odd

   std::cout << (((code1%2) && !(code2%2))? "no" : "yes") << std::endl;

}

void task_2001() {
   std::vector<unsigned short> numbers;

   std::copy(std::istream_iterator<unsigned short>(std::cin),
             std::istream_iterator<unsigned short>(),
             std::back_inserter(numbers));

   //after solving the system of equations: a1 - a3, b1 - b2

   std::cout << numbers[0] - numbers[4] << " " << numbers[1] - numbers[3] << std::endl;
}

void task_2012(){
   constexpr int tasksLeft = 4*60/45;

   unsigned short f;
   std::cin >> f;

   std::cout << (f + tasksLeft >= 12 ? "YES" : "NO") << std::endl;
}

