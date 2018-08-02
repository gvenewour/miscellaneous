#include "lib.h"
#include "homework2/ip_pool.h"

using namespace std;

int main(int argc, char *argv[])
{
    homework2::IpPool pool{};

    pool.sortReverse();
    pool.print();

    {
        homework2::Octet first{1}, second{70};
        pool.printFilteredBy(first);

        first = 46;
        pool.printFilteredBy(first, second);
    }

    homework2::Octet octet = 46;
    pool.printFilteredByAny(octet);

    return 0;
}
