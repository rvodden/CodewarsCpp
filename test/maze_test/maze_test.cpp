//
// Created by Richard Vodden on 23/04/2022.
//
#include <gtest/gtest.h>

#include "maze.h"

using maze::Maze;

TEST(maze, construction) {
  Maze maze = Maze(".W.\n.W.\n...");
  maze.print();
}