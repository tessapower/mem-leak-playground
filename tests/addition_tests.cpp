#include <gtest/gtest.h>
#include <my_lib/my_lib.h>

TEST(myLib, addition) {
  const int x = 1;
  const int y = 2;

  EXPECT_EQ(add(x, y), 3);
}
