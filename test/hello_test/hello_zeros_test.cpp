#include "hello.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using hello::zeros;

TEST(libhelloTest, zeros) {
  EXPECT_EQ(zeros(0), 0);
  EXPECT_EQ(zeros(6), 1);
  EXPECT_EQ(zeros(30), 7);
  EXPECT_EQ(zeros(100), 24);
  EXPECT_EQ(zeros(1000), 249);
  EXPECT_EQ(zeros(100000), 24999);
  EXPECT_EQ(zeros(1000000000), 249999998);
}
