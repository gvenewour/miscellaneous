//#include "lib.h"

/** @file
* @brief Решение ДЗ-02
*/

#include <iostream>
#include "ip_pool.h"

int main(int argc, char *argv[])
{
   /* [homework2-main] */

   homework2::IpPool pool{std::cin};

   pool.sortReverse();
   pool.print();

   homework2::Octet first{1}, second{70}, octet{46};
   pool.printBy(first);
   first = 46;
   pool.printBy(first, second);
   pool.printByAny(octet);

    /* [homework2-main] */

    return 0;
}
