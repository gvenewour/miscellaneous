/** @file
* @brief Примеры работы std::map с @ref homework3::LinearStatefulAllocator
*/

#include <map>

#include "common.h"
#include "examples_custom_allocator.h"
#include "linear_allocator.h"

namespace homework3 {
    using CustomMap = std::map<Key, Val, std::less<>, homework3::LinearStatefulAllocator<std::pair<const Key, Val>, maxCount> >;

    void examplesCustomAllocator() {
        exampleDefault();
        exampleCopyCtor();
        exampleMoveCtor();
        exampleSwap();
        exampleCopyAssignment();
        exampleMoveAssignment();
    }

    void exampleDefault() {
        std::cout << "==== Default allocator example ====" << "\n";
        CustomMap map{};
        fill<CustomMap>(map);
        std::cout << "--- map: ";
        print<CustomMap>(map);
    }

    void exampleCopyCtor() {
        std::cout << "==== Container copy constructor example ====" << "\n";

        std::cout << "--- constructing src --- " << "\n";
        CustomMap src{};
        fill<CustomMap>(src);
        std::cout << "--- src: ";
        print<CustomMap>(src);

        std::cout << "--- copy constructing dest --- " << "\n";
        auto dest = src;
        std::cout << "--- changed a single element in src --- " << "\n";

        src[0] = 100500;

        std::cout << "--- src: ";
        print<CustomMap>(src);
        std::cout << "--- dest (copy): ";
        print<CustomMap>(dest);
    }

    void exampleMoveCtor() {
        std::cout << "==== Container move constructor example ====" << "\n";
        std::cout << "--- constructing src --- " << "\n";
        CustomMap src{};
        fill<CustomMap>(src);

        std::cout << "--- move constructing dest --- " << "\n";
        auto dest = std::move(src);

        std::cout << "--- src after move: ";
        print<CustomMap>(src);
        std::cout << "--- dest after move: ";
        print<CustomMap>(dest);

        //works only with gcc>=5.5 - https://gcc.gnu.org/viewcvs/gcc?view=revision&revision=238647
        //std::cout << "adding elements to src after move" << "\n";
        //fill<CustomMap>(src);
        //std::cout << "src is valid: "; print<CustomMap>(src);
    }

    void exampleSwap() {
        std::cout << "==== Container swap example ====" << "\n";

        std::cout << "--- constructing src1 --- " << "\n";
        CustomMap src1;
        fill<CustomMap>(src1);
        src1[0] = 12345;

        std::cout << "--- constructing src2 --- " << "\n";

        CustomMap src2;
        fill<CustomMap>(src2);

        std::cout << "--- src1 before swap: ";
        print<CustomMap>(src1);
        std::cout << "--- src2 before swap : ";
        print<CustomMap>(src2);

        std::swap(src1, src2);

        std::cout << "--- src1 after swap: ";
        print<CustomMap>(src1);
        std::cout << "--- src2 after swap: ";
        print<CustomMap>(src2);
    }

    void exampleCopyAssignment() {
        std::cout << "==== Container copy assignment example  ====" << "\n";

        std::cout << "--- constructing src --- " << "\n";
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        std::cout << "--- constructing dest --- " << "\n";

        CustomMap dest;
        fill<CustomMap>(dest);
        dest[0] = 7777;

        std::cout << "--- src before copy assignment: ";
        print<CustomMap>(src);
        std::cout << "--- dest before copy assignment: ";
        print<CustomMap>(dest);

        dest = src;

        std::cout << "--- src after copy assignment: ";
        print<CustomMap>(src);
        std::cout << "--- dest after copy assignment: ";
        print<CustomMap>(dest);
    }

    void exampleMoveAssignment() {
        std::cout << "==== Container move assignment example  ====" << "\n";

        std::cout << "--- constructing src --- " << "\n";
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        std::cout << "--- constructing dest --- " << "\n";
        CustomMap dest;
        dest[0] = 4321; //and number of allocations on move will be less than the the number of constructs (by one)
        // fill<CustomMap>(dest); src[1] = 7777; //can be uncommented

        std::cout << "--- src before move assignment: ";
        print<CustomMap>(src);
        std::cout << "--- dest before move assignment: ";
        print<CustomMap>(dest);

        dest = std::move(src);

        std::cout << "--- src after move assignment: ";
        print<CustomMap>(src);
        std::cout << "--- dest after move assignment: ";
        print<CustomMap>(dest);

        //src[11] = 1234; src[12] = 3456; //will throw, need to uncomment _arena->deallocate in the allocator
    }
}