#include "gtest/gtest.h"
using namespace std;

class DummyTestSuite : public ::testing::Test{
public:
    DummyTestSuite(){};
    virtual ~DummyTestSuite(){};
};
TEST_F(DummyTestSuite, DummiestTestEver){
    ASSERT_TRUE(true);
}

