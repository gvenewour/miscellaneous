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
        LOG(INFO) << "--- Default allocator example ---";
        exampleDefault();
        LOG(INFO) << "---\n";

        LOG(INFO) << "--- Container copy constructor example ---";
        exampleCopyCtor();
        LOG(INFO) << "---\n";

        LOG(INFO) << "--- Container move constructor example ---";
        exampleMoveCtor();
        LOG(INFO) << "---\n";
//        exampleSwap();
//        LOG(INFO) << "---\n";
        LOG(INFO) << "--- Container copy assignment example ---";
        exampleCopyAssignment();
        LOG(INFO) << "---\n";

        LOG(INFO) << "--- Container move assignment example ---";
        exampleMoveAssignment();
        LOG(INFO) << "---\n";
    }

    void exampleDefault() {
        CustomMap map{};
        fill<CustomMap>(map);
        LOG(INFO) << "map: " << toKeyValString<CustomMap>(map);
    }

    void exampleCopyCtor() {
        LOG(INFO) << "constructing src";
        CustomMap src{};
        fill<CustomMap>(src);
        LOG(INFO) << "src: " << toKeyValString<CustomMap>(src);

        LOG(INFO) << "copy constructing dest";
        auto dest = src;
        LOG(INFO) << "changed a single element in src";

        src[0] = 100500;

        LOG(INFO) << "src:  " << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest: " << toKeyValString<CustomMap>(dest);
    }

    void exampleMoveCtor() {
        LOG(INFO) << "constructing src";
        CustomMap src{};
        fill<CustomMap>(src);

        LOG(INFO) << "move constructing dest";
        auto dest = std::move(src);

        LOG(INFO) << "src after move:  "  << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest after move: " << toKeyValString<CustomMap>(dest);

        //works only with gcc>=5.5 - https://gcc.gnu.org/viewcvs/gcc?view=revision&revision=238647
        //std::cout << "adding elements to src after move" << "\n";
        //fill<CustomMap>(src);
        //std::cout << "src is valid: "; print<CustomMap>(src);
    }

//    void exampleSwap() {
//        LOG(INFO) << "--- Container swap example ---";
//
//        LOG(INFO) << "constructing src1";
//        CustomMap src1;
//        fill<CustomMap>(src1);
//        src1[0] = 12345;
//
//        LOG(INFO) << "constructing src2";
//
//        CustomMap src2;
//        fill<CustomMap>(src2);
//
//        LOG(INFO) << "src1 before swap: "  << toKeyValString<CustomMap>(src1);
//        LOG(INFO) << "src2 before swap: "  << toKeyValString<CustomMap>(src2);
//
//        std::swap(src1, src2);
//
//        LOG(INFO) << "src1 after swap: " << toKeyValString<CustomMap>(src1);
//        LOG(INFO) << "src2 after swap: " << toKeyValString<CustomMap>(src2);
//    }

    void exampleCopyAssignment() {
        LOG(INFO) << "constructing src";
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        LOG(INFO) << "constructing dest";

        CustomMap dest;
        fill<CustomMap>(dest);
        dest[0] = 7777;

        LOG(INFO) << "src before copy assignment:  " << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest before copy assignment: " << toKeyValString<CustomMap>(dest);

        dest = src;

        LOG(INFO) << "src after copy assignment:  " << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest after copy assignment: " << toKeyValString<CustomMap>(dest);
    }

    void exampleMoveAssignment() {
        LOG(INFO) << "constructing src";
        CustomMap src;
        fill<CustomMap>(src);
        src[0] = 6666;

        LOG(INFO) << "constructing dest";
        CustomMap dest;
        dest[0] = 4321; //and number of allocations on move will be less than the the number of constructs (by one)
        // fill<CustomMap>(dest); src[1] = 7777; //can be uncommented

        LOG(INFO) << "src before move assignment:  " << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest before move assignment: " << toKeyValString<CustomMap>(dest);

        dest = std::move(src);

        LOG(INFO) << "src after move assignment:  " << toKeyValString<CustomMap>(src);
        LOG(INFO) << "dest after move assignment: " << toKeyValString<CustomMap>(dest);

        //src[11] = 1234; src[12] = 3456; //will throw, need to uncomment _arena->deallocate in the allocator
    }
}