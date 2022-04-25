#include "maze.h"

namespace maze {

using std::bitset;
using std::vector;

void Maze::calculate_neighbours() {
  // declare row iterators
  vector<vector<maze_data_t>>::iterator prev_row_iterator;
  vector<vector<maze_data_t>>::iterator curr_row_iterator;
  vector<vector<maze_data_t>>::iterator next_row_iterator;

  // declare cell iterators
  bool curr_row_prev_cell_value;
  vector<maze_data_t>::iterator curr_row_curr_cell_iterator;
  vector<maze_data_t>::iterator curr_row_next_cell_iterator;
  vector<maze_data_t>::iterator prev_row_curr_cell_iterator;
  vector<maze_data_t>::iterator next_row_curr_cell_iterator;

  // flags

  bool first_row = true;
  bool first_cell_of_row = true;
  bool last_cell_of_row = false;
  bool last_row = false;

  std::size_t rows;
  std::size_t cells;

  // initialize row iterators
  prev_row_iterator = curr_row_iterator = this->grid.begin();
  next_row_iterator = std::next(curr_row_iterator);
  rows = 0;
  do {
    if(rows == this->dimension[1] - 1) last_row = true;

    // initialize cell iterators
    curr_row_curr_cell_iterator = curr_row_iterator->begin();
    curr_row_next_cell_iterator = std::next(curr_row_curr_cell_iterator);
    if(!first_row) prev_row_curr_cell_iterator = prev_row_iterator->begin();
    if(!last_row) next_row_curr_cell_iterator = next_row_iterator->begin();

    cells = 0;
    do {
      if(cells == this->dimension[0] - 1) last_cell_of_row = true;

      curr_row_curr_cell_iterator->set(MAZE_NORTH_CLEAR, first_row ? false : !(*prev_row_curr_cell_iterator)[MAZE_WALL]);
      curr_row_curr_cell_iterator->set(MAZE_EAST_CLEAR, last_cell_of_row ? false : !(*curr_row_next_cell_iterator)[MAZE_WALL]);
      curr_row_curr_cell_iterator->set(MAZE_SOUTH_CLEAR, last_row ? false : !(*next_row_curr_cell_iterator)[MAZE_WALL]);
      curr_row_curr_cell_iterator->set(MAZE_WEST_CLEAR, first_cell_of_row ? false : !curr_row_prev_cell_value);

      // increment cell iterators
      curr_row_prev_cell_value = (*curr_row_curr_cell_iterator)[MAZE_WALL];
      curr_row_curr_cell_iterator++;
      if (!last_cell_of_row) curr_row_next_cell_iterator++;
      if (!first_row) prev_row_curr_cell_iterator++;
      if (!last_row) next_row_curr_cell_iterator++;

      // update metadata
      first_cell_of_row = false;
      last_cell_of_row = false;
      cells++;
    } while (cells < this->dimension[0]);

    // increment row iterators
    if(!first_row) prev_row_iterator++;
    curr_row_iterator++;
    next_row_iterator++;

    // update metadata
    first_row = false;
    first_cell_of_row = true;
    rows++;
  } while (rows < this->dimension[1]);
}

} // namespace maze