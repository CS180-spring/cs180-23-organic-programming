CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(OrganicDB)

ADD_SUBDIRECTORY(googletest)

include_directories(
    ./
    ./googletest/googletest/include/
)

ADD_EXECUTABLE(test
    test.cpp
    UserAccount.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)