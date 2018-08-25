# Find libstdc++.
macro(find_cppfs)
    find_library(CPPFS_LIBRARY stdc++fs
                 /usr/lib/gcc/x86_64-linux-gnu/6
                 /usr/lib/gcc/x86_64-linux-gnu/5
                 /usr/lib/x86_64-linux-gnu/
                 /usr/local/lib64/
                 /usr/lib64/
                 /usr/lib/)
    if(CPPFS_LIBRARY)
        SET(CPPFS_LIBRARY_FOUND true)
        MESSAGE(STATUS "Found stdc++fs library: ${CPPFS_LIBRARY}")
    else()
        SET(CPPFS_LIBRARY_FOUND false)
        MESSAGE(ERROR "stdc++fs not found")
    endif(CPPFS_LIBRARY)

    mark_as_advanced(CPPFS_LIBRARY)

endmacro()