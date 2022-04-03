#include "hello.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using hello::countSmileys;
using hello::getCount;
using hello::square_digits;
using hello::to_camel_case;
using testing::StrEq;

TEST(libhelloTest, squareDigits) {
  EXPECT_EQ(square_digits(3121), 9141);
  EXPECT_EQ(square_digits(2112), 4114);
  EXPECT_EQ(square_digits(0), 0);
  EXPECT_EQ(square_digits(13579), 19254981);
  EXPECT_EQ(square_digits(24680), 41636640);
}

TEST(libhelloTest, getCount) { EXPECT_EQ(getCount("abracadabra"), 5); }

TEST(libhelloTest, countSmileys) {
  EXPECT_EQ(countSmileys({}), 0);
  EXPECT_EQ(countSmileys({":D", ":~)", ";~)", ":)"}), 4);
  EXPECT_EQ(countSmileys({":)", ":(", ":D", ":O", ":;"}), 2);
  EXPECT_EQ(countSmileys({";]", ":[", ";*", ":$", ";-D"}), 1);
}

TEST(libhelloTest, toCamelCase) {
  EXPECT_THAT(to_camel_case(""), StrEq(""));
  EXPECT_THAT(to_camel_case("the_stealth_warrior"), StrEq("theStealthWarrior"));
  EXPECT_THAT(to_camel_case("The-Stealth-Warrior"), StrEq("TheStealthWarrior"));
  EXPECT_THAT(to_camel_case("A-B-C"), StrEq("ABC"));
}