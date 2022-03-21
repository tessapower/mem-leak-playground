FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_executable(test_addition    addition_tests.cpp)
add_executable(test_subtraction subtraction_tests.cpp)
# Add more tests here

target_link_libraries(test_addition    PRIVATE my_lib gtest gtest_main)
target_link_libraries(test_subtraction PRIVATE my_lib gtest gtest_main)
# Link above test to gtest here

add_test(NAME addition    COMMAND test_addition)
add_test(NAME subtraction COMMAND test_subtraction)
# Add executable for test here so it shows up in build configurations
