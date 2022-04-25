//
// Created by Richard Vodden on 23/04/2022.
//

#include "maze.h"

#include <bitset>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace maze {

using std::bitset;
using std::vector;

Maze::Maze(std::string const& input) {
  std::size_t const width  = input.find_first_of('\n');
  std::size_t const height = input.size() / width;

  if ((width + 1) * height - 1 != input.size()) {
    throw new std::domain_error("Maze grids must have constant row length.");
  }

  this->dimension.push_back(width);
  this->dimension.push_back(height);

  this->grid = vector<vector<maze_data_t>>(height, vector<maze_data_t>(width, maze_data_t()));

  std::stringstream input_stream = std::stringstream{input};
  std::string line;

  for (vector<maze_data_t>& row : this->grid) {
    std::getline(input_stream, line);
    std::string::iterator line_iterator = line.begin();

    for (maze_data_t& cell : row) {
      cell.set(MAZE_WALL, (*line_iterator == 'W'));
      line_iterator++;
    }
  }
  calculate_neighbours();
}

void Maze::print() {
  vector<vector<bitset<4>>> wall_view = this->wall_view();

  std::cout << "(" << this->dimension[0] << "," << this->dimension[1] << ")" << std::endl;

  for (vector<bitset<4>> const& row : wall_view) {
    for (bitset<4> const& cell : row) {
      std::cout << characters.at(cell.to_ulong());
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  /* print out neighbours for debugging purposes */
  std::cout << "WSEN WSEN WSEN WSEN WSEN" << std::endl;
  for (vector<bitset<4>> const& row : wall_view) {
    for (bitset<4> const& cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "WTWSEN WTWSEN WTWSEN" << std::endl;
  for (vector<maze_data_t> const& row : this->grid) {
    for (maze_data_t const& cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

vector<vector<bitset<4>>> Maze::wall_view() {
  // initialize the view with empty cells
  vector<vector<bitset<4>>> wall_view(this->dimension[1] + 2,
                                      vector<bitset<4>>(this->dimension[0] + 2, bitset<4>{0xf}));

  // iterators
  vector<vector<bitset<4>>>::iterator view_row_iterator;
  vector<vector<maze_data_t>>::iterator grid_row_iterator;
  vector<bitset<4>>::iterator view_cell_iterator;
  vector<maze_data_t>::iterator grid_cell_iterator;
  std::size_t row;
  std::size_t cell;

  // flags
  bool first_row         = true;
  bool last_row          = false;
  bool first_cell_of_row = true;
  bool last_cell_of_row  = false;

  // drop the corners in
  wall_view.front().front() = 0x19;  // NOLINT(readability-magic-numbers)
  wall_view.front().back()  = 0x13;  // NOLINT(readability-magic-numbers)
  wall_view.back().front()  = 0x1c;  // NOLINT(readability-magic-numbers)
  wall_view.back().back()   = 0x16;  // NOLINT(readability-magic-numbers)

  // initialize row iterators
  row               = 0;
  view_row_iterator = wall_view.begin();
  grid_row_iterator = this->grid.begin();

  //  std::cout << "(" << this->dimension[0] << "," << this->dimension[1] << ")"
  //  << std::endl;

  do {
    cell = 0;
    std::cout << "New Row: " << row << std::endl;
    // initialize cell iterators
    view_cell_iterator = view_row_iterator->begin();
    grid_cell_iterator = grid_row_iterator->begin();

    do {
      std::cout << "(" << cell << "," << row << ")" << " First Row : "
      << first_row << "; Last Row : "
                << last_row << "; First Cell : " << first_cell_of_row <<
                "; Last Cell : " << last_cell_of_row << "; Maze Data: " << (*grid_cell_iterator) << std::endl;

      // process corners
      if ((first_row or last_row) and (first_cell_of_row or last_cell_of_row)) {
        // do nothing as corner already processed
      } else if (first_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = true;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = false;
      } else if (last_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = true;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = false;
      } else if (first_cell_of_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = true;
      } else if (last_cell_of_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = true;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = !(*grid_cell_iterator)[MAZE_WALL];
      } else if ((*grid_cell_iterator)[MAZE_WALL])
        *view_cell_iterator = grid_cell_iterator->to_ulong() & MAZE_NEIGHBOURS;

      // increment cell iterators
      cell++;
      last_cell_of_row = (cell == this->dimension[0] + 1);
      if (!first_cell_of_row and !last_cell_of_row) grid_cell_iterator++;
      view_cell_iterator++;
      first_cell_of_row = false;
    } while (view_cell_iterator != view_row_iterator->end());

    // increment row iterators
    row++;
    if (row == this->dimension[1] + 1) last_row = true;
    if (!first_row and !last_row) grid_row_iterator++;
    view_row_iterator++;
    first_cell_of_row = true;
    first_row = false;
  } while (view_row_iterator != wall_view.end());

  return wall_view;
}

}  // namespace maze