#include "lib.h"
#include "ip_pool.h"

int main(int argc, char *argv[])
{
    fs::path path{"ip_filter.tsv"};
    homework2::IpPool pool{path};

    std::cout << pool.size() << "\n";

    pool.sortReverse();
    pool.print();

    homework2::Octet first{1}, second{70}, octet{46};
    pool.printFilteredBy(first);
    first = 46;
    pool.printFilteredBy(first, second);
    pool.printFilteredByAny(octet);

    return 0;
}
