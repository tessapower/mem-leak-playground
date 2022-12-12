#include <cstdlib>
#include <cstring>
#include <iostream>

#include "leaks.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: mem_leak <example>\n"
                  << "\n"
                  << "Examples:\n"
                  << "  missing_delete   new[] without delete[]\n"
                  << "  lost_pointer     pointer reassignment leaks original\n"
                  << "  error_path       early return skips cleanup\n"
                  << "  container        vector<T*>::clear() without delete\n"
                  << "  circular         shared_ptr reference cycle\n"
                  << "  all              run all examples\n";
        return EXIT_FAILURE;
    }

    const char* name = argv[1];

    if (std::strcmp(name, "missing_delete") == 0 || std::strcmp(name, "all") == 0)
        missing_delete();
    if (std::strcmp(name, "lost_pointer") == 0 || std::strcmp(name, "all") == 0)
        lost_pointer();
    if (std::strcmp(name, "error_path") == 0 || std::strcmp(name, "all") == 0)
        error_path();
    if (std::strcmp(name, "container") == 0 || std::strcmp(name, "all") == 0)
        container_of_raw_ptrs();
    if (std::strcmp(name, "circular") == 0 || std::strcmp(name, "all") == 0)
        circular_shared_ptr();

    return EXIT_SUCCESS;
}
