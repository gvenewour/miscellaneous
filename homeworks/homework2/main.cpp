//#include "lib.h"
#include <iostream>
#include "ip_pool.h"

int main(int argc, char *argv[])
{
   homework2::IpPool pool{std::cin};

   pool.sortReverse();
   pool.print();

   homework2::Octet first{1}, second{70}, octet{46};
   pool.printBy(first);
   first = 46;
   pool.printBy(first, second);
   pool.printByAny(octet);

    return 0;
}
