//
// Created by Richard Vodden on 19/04/2022.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "hello.h"

using hello::maxSequence;

TEST(libhelloTest, maxSequence) {
  EXPECT_EQ(maxSequence({}), 0);
  EXPECT_EQ(maxSequence({-2, 1, -3, 4, -1, 2, 1, -5, 4}), 6);
}