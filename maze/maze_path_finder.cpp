//
// Created by Richard Vodden on 23/04/2022.
//

#include <bitset>
#include <iostream>

#include "maze.h"

namespace maze {

using std::bitset;
using std::vector;

bool Maze::path_finder() {
  vector<std::size_t> dimension = {this->grid.front().size(), this->grid.size()};

  vector<vector<bool>> visited(dimension[1], vector<bool>(dimension[0], false));

  return _path_finder({0, 0}, visited);
}

bool Maze::_path_finder(const std::vector<size_t>& location, vector<vector<bool>>& visited) {

  maze_data_t const& maze_data = this->grid.at(location[1]).at(location[0]);

  if (maze_data[MAZE_TARGET])
    return true;

  if (visited[location[1]][location[0]])
    return false;

  visited[location[1]][location[0]] = true;

  std::vector<std::vector<size_t>> next_step = {
      {location[0], location[1] - 1}, // North
      {location[0] + 1, location[1]}, // East
      {location[0], location[1] + 1}, // South
      {location[0] - 1, location[1]}  // West
  };

  for(char neighbour = 0; neighbour < 4; neighbour++)
    if (maze_data[neighbour] and _path_finder(next_step[neighbour],  visited) )
      return true;
  return false;

}

}  // namespace maze