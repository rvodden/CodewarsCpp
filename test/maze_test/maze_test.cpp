//
// Created by Richard Vodden on 23/04/2022.
//
#include "maze.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace maze_test {

using maze::Maze;
using maze::MazeBuilder;
using maze::MazePrinter;

using testing::Eq;

typedef std::pair<std::string, bool> maze_test_t;

class MazeTest : public testing::TestWithParam<maze_test_t> {
 public:
  void SetUp() override {
    maze_test_t pair = GetParam();
    maze_string      = pair.first;
    expected_result  = pair.second;
  };

 protected:
  std::string maze_string;
  bool expected_result;
};

TEST_P(MazeTest, construction) {
  Maze maze = MazeBuilder::build(maze_string);
  MazePrinter::print(maze);
  EXPECT_THAT(maze.path_finder(), Eq(expected_result));
}

INSTANTIATE_TEST_SUITE_P(ParameterizedMazeTest, MazeTest,
                         testing::Values(
                             maze_test_t({".W.\n.W.\n...", true}),
                             maze_test_t({".W.\n.W.\nW..", false}),
                             maze_test_t({"......\n......\n......\n......\n......\n......", true}),
                             maze_test_t({"......\n......\n......\n......\n.....W\n....W.", false})
                             )
                         );

}  // namespace maze_test