#include <iostream>

#include "maze.h"

namespace maze {

using std::vector;


void MazePrinter::print(Maze const& maze) {
  vector<std::size_t> dimension { maze.grid.front().size(), maze.grid.size() };
  vector<vector<maze_view_t>> wall_view = MazePrinter::wall_view(maze.grid, dimension);

  std::cout << "(" << dimension[0] << "," << dimension[1] << ")" << std::endl;

  for (vector<maze_view_t> const& row : wall_view) {
    for (maze_view_t const& cell : row) {
      std::cout << characters.at(cell.to_ulong());
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  //  std::cout << "EWSEN EWSEN EWSEN EWSEN EWSEN" << std::endl;
  //  for (vector<maze_view_t> const& row : wall_view) {
  //    for (maze_view_t const& cell : row) {
  //      std::cout << cell << " ";
  //    }
  //    std::cout << std::endl;
  //  }
  //  std::cout << std::endl;
  //
  //  std::cout << "WTWSEN WTWSEN WTWSEN" << std::endl;
  //  for (vector<maze_data_t> const& row : this->grid) {
  //    for (maze_data_t const& cell : row) {
  //      std::cout << cell << " ";
  //    }
  //    std::cout << std::endl;
  //  }
  //  std::cout << std::endl;
}

vector<vector<maze_view_t>> MazePrinter::wall_view(vector<vector<maze_data_t>> const& grid, vector<std::size_t> const& dimension) {
  // initialize the view with empty cells
  vector<vector<maze_view_t>> wall_view = vector<vector<maze_view_t>>(dimension[1] + 2,
                                                                      vector<maze_view_t>(dimension[0] + 2, maze_view_t{0xf}));

  // iterators
  vector<vector<maze_view_t>>::iterator view_row_iterator;
  vector<vector<maze_data_t>>::const_iterator grid_row_iterator;
  vector<maze_view_t>::iterator view_cell_iterator;
  vector<maze_data_t>::const_iterator grid_cell_iterator;
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
  grid_row_iterator = grid.cbegin();

  //  std::cout << "(" << this->dimension[0] << "," << this->dimension[1] << ")"
  //  << std::endl;

  do {
    cell = 0;
    //    std::cout << "New Row: " << row << std::endl;
    // initialize cell iterators
    view_cell_iterator = view_row_iterator->begin();
    grid_cell_iterator = grid_row_iterator->cbegin();

    do {
      //      std::cout << "(" << cell << "," << row << ")"
      //                << " First Row : " << first_row << "; Last Row : " << last_row << "; First Cell : " << first_cell_of_row
      //                << "; Last Cell : " << last_cell_of_row << "; Maze Data: " << (*grid_cell_iterator) << std::endl;

      // process corners
      if ((first_row or last_row) and (first_cell_of_row or last_cell_of_row)) {
        // do nothing as corner already processed
      } else if (first_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = true;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_EDGE]        = true;
      } else if (last_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = true;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = false;
        (*view_cell_iterator)[MAZE_EDGE]        = true;
      } else if (first_cell_of_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = true;
        (*view_cell_iterator)[MAZE_EDGE]        = true;
      } else if (last_cell_of_row) {
        (*view_cell_iterator)[MAZE_NORTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_EAST_CLEAR]  = true;
        (*view_cell_iterator)[MAZE_SOUTH_CLEAR] = false;
        (*view_cell_iterator)[MAZE_WEST_CLEAR]  = !(*grid_cell_iterator)[MAZE_WALL];
        (*view_cell_iterator)[MAZE_EDGE]        = true;
      } else if ((*grid_cell_iterator)[MAZE_WALL])
        *view_cell_iterator = grid_cell_iterator->to_ulong() & MAZE_NEIGHBOURS;

      // increment cell iterators
      cell++;
      last_cell_of_row = (cell == dimension[0] + 1);
      if (!first_cell_of_row and !last_cell_of_row) grid_cell_iterator++;
      view_cell_iterator++;
      first_cell_of_row = false;
    } while (view_cell_iterator != view_row_iterator->end());

    // increment row iterators
    row++;
    if (row == dimension[1] + 1) last_row = true;
    if (!first_row and !last_row) grid_row_iterator++;
    view_row_iterator++;
    first_cell_of_row = true;
    first_row         = false;
  } while (view_row_iterator != wall_view.end());

  // open up the entrance and exit
  wall_view[0][1] = 0xf;
  wall_view[dimension[0] + 1][dimension[1]] = 0xf;

  return wall_view;
}

} // namespace maze