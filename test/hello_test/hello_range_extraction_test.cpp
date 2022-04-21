#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "hello.h"

using hello::range_extraction;

using testing::StrEq;

TEST(libhelloTest, rangeExtration ) {
  EXPECT_THAT(range_extraction({-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20}), StrEq("-6,-3-1,3-5,7-11,14,15,17-20"));
  EXPECT_THAT(range_extraction({-3,-2,-1,2,10,15,16,18,19,20}), StrEq("-3--1,2,10,15,16,18-20"));
}