#include <iostream>
#include <sstream>

#include "maze.h"

namespace maze {

Maze MazeBuilder::build(std::string const& input) {
  std::size_t const width  = input.find_first_of('\n');
  std::size_t const height = input.size() / width;

  if ((width + 1) * height - 1 != input.size()) {
    throw new std::domain_error("Maze grids must have constant row length.");
  }

  vector<vector<maze_data_t>>* grid = new vector<vector<maze_data_t>>(height, vector<maze_data_t>(width, maze_data_t()));

  std::stringstream input_stream = std::stringstream{input};
  std::string line;

  for (vector<maze_data_t>& row : *grid) {
    std::getline(input_stream, line);
    std::string::iterator line_iterator = line.begin();

    for (maze_data_t& cell : row) {
      cell.set(MAZE_WALL, (*line_iterator == 'W'));
      line_iterator++;
    }
  }
  MazeBuilder::calculate_neighbours(*grid);

  // set target
  (*grid)[width - 1][height - 1][MAZE_TARGET] = true;
  return Maze(*grid);
}

} // namespace maze