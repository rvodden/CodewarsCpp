#include "hello.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using hello::pick_peaks;
using hello::PeakData;

using testing::ContainerEq;


PeakData actual, expected;

TEST(libhelloTest, pickPeaks) {
  actual = pick_peaks(std::vector<int>{3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3});
  expected = {.pos = {3, 7}, .peaks = {6, 3}};
  EXPECT_THAT(actual.pos, ContainerEq(expected.pos));
  EXPECT_THAT(actual.peaks, ContainerEq(expected.peaks));
}

TEST(libhelloTest, pickPeaks2) {
  actual = pick_peaks(std::vector<int>{1, 2, 2, 2, 1});
  expected = {.pos = {1}, .peaks = {2}};
  EXPECT_THAT(actual.pos, ContainerEq(expected.pos));
  EXPECT_THAT(actual.peaks, ContainerEq(expected.peaks));
}

TEST(libhelloTest, pickPeaks3) {
  actual = pick_peaks(std::vector<int>{1, 2, 2, 2, 3});
  expected = {.pos = {}, .peaks = {}};
  EXPECT_THAT(actual.pos, ContainerEq(expected.pos));
  EXPECT_THAT(actual.peaks, ContainerEq(expected.peaks));
}

TEST(libhelloTest, pickPeaks4) {
  actual = pick_peaks(std::vector<int>{2, 1, 3, 2, 2, 2, 2, 1});
  expected = {.pos = {2}, .peaks = {3}};
  EXPECT_THAT(actual.pos, ContainerEq(expected.pos));
  EXPECT_THAT(actual.peaks, ContainerEq(expected.peaks));
}

TEST(libhelloTest, pickPeaks5) {
  actual = pick_peaks(std::vector<int>{1,2,5,4,3,2,3,6,4,1,2,3,3,4,5,3,2,1,2,3,5,5,4,3});
  expected = {.pos = {2, 7, 14, 20}, .peaks = {5, 6, 5, 5}};
  EXPECT_THAT(actual.pos, ContainerEq(expected.pos));
  EXPECT_THAT(actual.peaks, ContainerEq(expected.peaks));
}
