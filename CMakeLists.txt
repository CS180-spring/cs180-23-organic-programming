CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

project(OrganicDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



ADD_SUBDIRECTORY(googletest)

include_directories(
    ./
    ./googletest/googletest/include/
)

ADD_EXECUTABLE(test
    tests/test.cpp
    Frontend/UserAccount.h
    Backend/Database.h
    Backend/Collection.h
)
ADD_EXECUTABLE(backEndTest
    Backend/backEndTest.cpp
)


TARGET_LINK_LIBRARIES(test gmock gtest gtest_main)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)