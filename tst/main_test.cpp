#include <gtest/gtest.h>

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

TEST(MAIN, HELLO){
    ASSERT_EQ("hello","hello");
}