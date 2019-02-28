#include "example_custom_list.h"

#include <algorithm>

#include "common.h"
#include "custom_list.h"
#include "linear_allocator.h"

/** @file
* @brief Function homework3::exampleCustomList
*/

namespace homework3 {
    void exampleCustomList() {
        homework3::CustomList<Val> list{0, 1, 2, 3, 4, 5, 6, 7, 8};
        list.insert(9);

        homework3::CustomList<Val, homework3::LinearStatefulAllocator<Val, maxCount> > customList{0, 1, 2, 3, 100};
        for (auto i = 5; i < maxCount; ++i) {
            customList.insert(i);
        }

        std::replace(customList.begin(), customList.end(), 100, 4);

        for (const auto& it: customList) {
            std::cout << it << " ";
        }
        std::cout << "\n";
    }
}