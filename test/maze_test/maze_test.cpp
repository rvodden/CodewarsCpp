//
// Created by Richard Vodden on 23/04/2022.
//
#include "maze.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace maze_test {

using maze::Maze;
using maze::MazeBuilder;
using maze::MazePrinter;

using testing::Eq;

typedef std::pair<std::string, unsigned int> shortest_path_t;

class ShortestPathTest : public testing::TestWithParam<shortest_path_t> {
 public:
  void SetUp() override {
    shortest_path_t pair = GetParam();
    maze_string          = pair.first;
    expected_result      = pair.second;
  };

 protected:
  std::string maze_string;
  int expected_result;
};

TEST_P(ShortestPathTest, shortestPath) {
  Maze maze = MazeBuilder::build(maze_string);
  MazePrinter::print(maze);
  EXPECT_THAT(maze.shortest_path(), Eq(expected_result));
}

INSTANTIATE_TEST_SUITE_P(MazeTest, ShortestPathTest,
                         testing::Values(shortest_path_t ({".W.\n.W.\n...", 4}),shortest_path_t ({".W.\n.W.\nW..", -1}),
                                         shortest_path_t ({"......\n......\n......\n......\n......\n......", 10}),
                                         shortest_path_t ({"......\n......\n......\n......\n.....W\n....W.", -1}),
                                         shortest_path_t ({".", 0}),
                                         shortest_path_t ({".............\n"
                                                      "WW.WWWWWWWWW.\n"
                                                      ".............\n"
                                                      ".WWW.WWWW.WWW\n"
                                                      ".............\n"
                                                      "WWWWW.WW.WWW.\n"
                                                      "...........W.\n"
                                                      ".W..WWWWWWWWW\n"
                                                      ".............\n"
                                                      "WWWWWWW.WW.W.\n"
                                                      ".............\n"
                                                      ".WW.WW.WWWWWW\n"
                                                      ".............\n",
                                                      30})

                                             ));

typedef std::pair<std::string, bool> path_finder_test_t;

class PathFinderTest : public testing::TestWithParam<path_finder_test_t> {
 public:
  void SetUp() override {
    path_finder_test_t pair = GetParam();
    maze_string             = pair.first;
    expected_result         = pair.second;
  };

 protected:
  std::string maze_string;
  bool expected_result;
};

TEST_P(PathFinderTest, shortestPath) {
  Maze maze = MazeBuilder::build(maze_string);
  MazePrinter::print(maze);
  EXPECT_THAT(maze.path_finder(), Eq(expected_result));
}

INSTANTIATE_TEST_SUITE_P(MazeTest, PathFinderTest,
                         testing::Values(path_finder_test_t({".W.\n.W.\n...", true}),
                                         path_finder_test_t({".W.\n.W.\nW..", false}),
                                         path_finder_test_t({"......\n......\n......\n......\n......\n......", true}),
                                         path_finder_test_t({"......\n......\n......\n......\n.....W\n....W.", false})
                                         ));
}  // namespace maze_test