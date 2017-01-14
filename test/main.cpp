#include <cstdio>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {

        ::testing::GTEST_FLAG(filter) = "-GprofTest.GprofTest";
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
