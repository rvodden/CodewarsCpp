#include <limits>
#include <iostream>

#include "maze.h"

namespace maze {

int Maze::shortest_path() {
  vector<std::size_t> dimension = {this->grid.front().size(), this->grid.size()};

  vector<vector<bool>> visited(dimension[1], vector<bool>(dimension[0], false));
  vector<vector<unsigned int>> cost(
      dimension[1],
      vector<unsigned int>(
          dimension[0], std::numeric_limits<unsigned int>::max())
  );

  cost[0][0] = 0;

  if (!path_finder()) return -1;
  return _shortest_path(visited, cost);
}

static inline vector<std::size_t> masked_minimum(vector<vector<unsigned int>> const& matrix, vector<vector<bool>> const& mask) {
  unsigned int min = std::numeric_limits<unsigned int>::max();
  unsigned int const* minimum_element = &min;

  std::size_t row = 0;
  std::size_t cell = 0;
  std::size_t min_row;
  std::size_t min_cell;

  vector<vector<bool>>::const_iterator mask_row = mask.cbegin();
  for(vector<unsigned int> const& matrix_row : matrix) {

    vector<bool>::const_iterator mask_cell = mask_row->cbegin();
    for(unsigned int const& matrix_cell: matrix_row) {

      if(!*mask_cell) {
        if (*minimum_element > matrix_cell) {
          minimum_element = &matrix_cell;
          min_row = row;
          min_cell = cell;
        }
      }

      mask_cell++;
      cell++;
    }

    mask_row++;
    cell = 0;
    row++;
  }

  return {min_cell, min_row};
}

unsigned int Maze::_shortest_path(vector<vector<bool>>& visited, vector<vector<unsigned int>>& cost) {
  std::vector<std::size_t> location;
  do {
    location = masked_minimum(cost, visited);
    visited[location[1]][location[0]] = true;
    maze_data_t const& maze_data = this->grid[location[1]][location[0]];
    unsigned int this_cost = cost[location[1]][location[0]];

    std::vector<std::vector<size_t>> next_steps = {
        {location[0], location[1] - 1}, // North
        {location[0] + 1, location[1]}, // East
        {location[0], location[1] + 1}, // South
        {location[0] - 1, location[1]}  // West
    };

    for(char neighbour = 0; neighbour < 4; neighbour++) {
      if(maze_data[neighbour]) {
        std::vector<size_t>& next_step = next_steps[neighbour];
        if (visited[next_step[1]][next_step[0]]) continue;
        if (cost[next_step[1]][next_step[0]] > this_cost + 1) cost[next_step[1]][next_step[0]] = this_cost + 1;
      }
    }
  } while(!this->grid[location[1]][location[0]][MAZE_TARGET]);
  return cost[location[1]][location[0]];
};

} // namespace maze