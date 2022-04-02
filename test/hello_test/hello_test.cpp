#include <gtest/gtest.h>

#include "hello.h"

using namespace hello;

TEST(libhello_test, square_digits){
    EXPECT_EQ(square_digits(3121), 9141);
    EXPECT_EQ(square_digits(2112), 4114);
    EXPECT_EQ(square_digits(0), 0);
    EXPECT_EQ(square_digits(13579), 19254981);
    EXPECT_EQ(square_digits(24680), 41636640);
}

TEST(libhello_test, getCount) {
    EXPECT_EQ(getCount("abracadabra"), 5);
}

TEST(libhello_test, countSmileys) {
    EXPECT_EQ(countSmileys({}),0);
    EXPECT_EQ(countSmileys({":D", ":~)", ";~)", ":)"}),4);
    EXPECT_EQ(countSmileys({":)", ":(", ":D", ":O", ":;"}),2);
    EXPECT_EQ(countSmileys({";]", ":[", ";*", ":$", ";-D"}),1);
}