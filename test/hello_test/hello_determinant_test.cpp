//
// Created by Richard Vodden on 21/04/2022.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "hello.h"

using hello::determinant;
using std::vector;
using testing::Eq;

TEST(libhelloTest, determinant) {
  EXPECT_THAT(
      determinant(vector<std::vector<long long> >{vector<long long>{1}}),
      Eq(1));
}

TEST(libhelloTest, determinant1) {
  EXPECT_THAT(determinant(vector<std::vector<long long> >{
                  vector<long long>{1, 3},
                  vector<long long>{2, 5},
              }),
              Eq(-1));
}

TEST(libhelloTest, determinant2) {
  EXPECT_THAT(determinant(vector< std::vector<long long> > {
              vector<long long> {2,  5,  3},
              vector<long long> {1, -2, -1},
              vector<long long> {1,  3,  4}
              }),
              Eq(-20));
}