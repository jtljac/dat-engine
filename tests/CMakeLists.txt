cmake_minimum_required(VERSION 3.22)

enable_testing()

find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

add_executable(dat-engine-tests
        unit-test.cpp
        vector-tests.cpp
        matrix-tests.cpp
#        dat-mat-test.cpp
#        dat-quat-tests.cpp
)

target_link_libraries(dat-engine-tests PRIVATE Catch2::Catch2)
target_link_libraries(dat-engine-tests PRIVATE dat-engine)

# Start Testing
catch_discover_tests(dat-engine-tests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})