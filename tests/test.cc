#include "include/buried.h"
#include "gtest/gtest.h"

TEST(BuriedPointTest, Test1) { Buried_Create("D:/tmp"); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}