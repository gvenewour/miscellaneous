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
        LOG(INFO) << "=== Default allocator example ===";
        CustomMap map{};
        fill<CustomMap>(map);
        LOG(INFO) << strafeLog("map: ") << print<CustomMap>(map);
    }

    void exampleCopyCtor() {
        LOG(INFO) << "=== Container copy constructor example ===";

        LOG(INFO) << strafeLog("constructing src");
        CustomMap src{};
        fill<CustomMap>(src);
        LOG(INFO) << "    src: " << print<CustomMap>(src);

        LOG(INFO) << strafeLog("copy constructing dest");
        auto dest = src;
        LOG(INFO) << "    changed a single element in src";

        src[0] = 100500;

        LOG(INFO) << "    src: "         << print<CustomMap>(src);
        LOG(INFO) << "    dest (copy): " << print<CustomMap>(dest);
    }

    void exampleMoveCtor() {
        LOG(INFO) << "=== Container move constructor example ===";
        LOG(INFO) << strafeLog("constructing src");
        CustomMap src{};
        fill<CustomMap>(src);

        LOG(INFO) << strafeLog("move constructing dest");
        auto dest = std::move(src);

        LOG(INFO) << strafeLog("src after move: ")  << print<CustomMap>(src);
        LOG(INFO) << strafeLog("dest after move: ") << print<CustomMap>(dest);

        //works only with gcc>=5.5 - https://gcc.gnu.org/viewcvs/gcc?view=revision&revision=238647
        //std::cout << "adding elements to src after move" << "\n";
        //fill<CustomMap>(src);
        //std::cout << "src is valid: "; print<CustomMap>(src);
    }

    void exampleSwap() {
        LOG(INFO) << "=== Container swap example ===";

        LOG(INFO) << strafeLog("constructing src1");
        CustomMap src1;
        fill<CustomMap>(src1);
        src1[0] = 12345;

        LOG(INFO) << strafeLog("constructing src2");

        CustomMap src2;
        fill<CustomMap>(src2);

        LOG(INFO) << strafeLog("src1 before swap: ")  << print<CustomMap>(src1);
        LOG(INFO) << strafeLog("src2 before swap: ") << print<CustomMap>(src2);

        std::swap(src1, src2);

        LOG(INFO) << strafeLog("src1 after swap: ") << print<CustomMap>(src1);
        LOG(INFO) << strafeLog("src2 after swap: ") << print<CustomMap>(src2);
    }

    void exampleCopyAssignment() {
        LOG(INFO) << "=== Container copy assignment example ===";

        LOG(INFO) << strafeLog("constructing src");
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        LOG(INFO) << strafeLog("constructing dest");

        CustomMap dest;
        fill<CustomMap>(dest);
        dest[0] = 7777;

        LOG(INFO) << strafeLog("src before copy assignment: ")  << print<CustomMap>(src);
        LOG(INFO) << strafeLog("dest before copy assignment: ") << print<CustomMap>(dest);

        dest = src;

        LOG(INFO) << strafeLog("src after copy assignment: ")  << print<CustomMap>(src);
        LOG(INFO) << strafeLog("dest after copy assignment: ") << print<CustomMap>(dest);
    }

    void exampleMoveAssignment() {
        LOG(INFO) << "=== Container move assignment example ===";

        LOG(INFO) << strafeLog("constructing src");
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        LOG(INFO) << strafeLog("constructing dest");
        CustomMap dest;
        dest[0] = 4321; //and number of allocations on move will be less than the the number of constructs (by one)
        // fill<CustomMap>(dest); src[1] = 7777; //can be uncommented

        LOG(INFO) << strafeLog("src before move assignment: ")  << print<CustomMap>(src);
        LOG(INFO) << strafeLog("dest before move assignment: ") << print<CustomMap>(dest);

        dest = std::move(src);

        LOG(INFO) << strafeLog("src after move assignment: ")  << print<CustomMap>(src);
        LOG(INFO) << strafeLog("dest after move assignment: ") << print<CustomMap>(dest);

        //src[11] = 1234; src[12] = 3456; //will throw, need to uncomment _arena->deallocate in the allocator
    }
}