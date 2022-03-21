#include <gtest/gtest.h>
#include <my_lib/my_lib.h>

TEST(myLib, subtraction) {
  const int x = 2;
  const int y = 1;

  EXPECT_EQ(subtract(x, y), 1);
}
