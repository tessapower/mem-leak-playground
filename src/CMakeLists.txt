set(MY_LIB_HEADERS
        "${scratch_project_SOURCE_DIR}/include/my_lib/my_lib.h"
        # Add other library headers here
        )

add_library(my_lib STATIC
        my_lib/my_lib.cpp
        # Add other source files here
        ${MY_LIB_HEADERS}
        )

# Support <my_lib/my_lib.h> imports in public headers
target_include_directories(my_lib PUBLIC ../include)
# Support "my_lib.h" imports in private headers and source files
target_include_directories(my_lib PRIVATE ../include/my_lib)
