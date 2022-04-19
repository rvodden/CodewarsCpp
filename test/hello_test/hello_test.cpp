#include "hello.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using hello::countSmileys;
using hello::getCount;
using hello::square_digits;
using hello::to_camel_case;
using hello::countBits;
using hello::digital_root;
using hello::countLetters;

using testing::StrEq;
using testing::ContainerEq;

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

TEST(libhelloTest, countBits) {
  EXPECT_EQ(countBits(0),0);
  EXPECT_EQ(countBits(4),1);
  EXPECT_EQ(countBits(7),3);
  EXPECT_EQ(countBits(9),2);
  EXPECT_EQ(countBits(10),2);
  EXPECT_EQ(countBits(26),3);
  EXPECT_EQ(countBits(77231418),14);
  EXPECT_EQ(countBits(12525589),11);
  EXPECT_EQ(countBits(3811),8);
  EXPECT_EQ(countBits(392902058),17);
}

TEST(libhelloTest, digitalRoot) {
  EXPECT_EQ(digital_root(16),7);
  EXPECT_EQ(digital_root(195),6);
  EXPECT_EQ(digital_root(992),2);
  EXPECT_EQ(digital_root(167346),9);
  EXPECT_EQ(digital_root(0),0);
}

TEST(libhelloTest, countLetters) {
  std::map<char, unsigned> m1 = {{'a',  2 }, {'b', 1}};
  std::map<char, unsigned> m2 = {};
  EXPECT_THAT(countLetters("aba"), ContainerEq(m1));
  EXPECT_THAT(countLetters(""), ContainerEq(m2));
}
