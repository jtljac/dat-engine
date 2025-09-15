cmake_minimum_required(VERSION 3.22)

CPMAddPackage("gh:catchorg/Catch2@3.10.0")
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(Catch)

add_executable(dat-engine-tests
        UnitTest.cpp
        VectorTests.cpp
        MatrixTests.cpp
        SparseMapTests.cpp
#        dat-mat-test.cpp
#        dat-quat-tests.cpp
)

target_link_libraries(dat-engine-tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(dat-engine-tests PRIVATE dat-engine)

# Start Testing
enable_testing()
catch_discover_tests(dat-engine-tests WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})