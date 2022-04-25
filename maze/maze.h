#include <string>
#include <vector>
#include <bitset>

#include <map>

#ifndef CODEWARS_MAZE_MAZE_H_
#define CODEWARS_MAZE_MAZE_H_

#define MAZE_DATA_BITS   6

#define MAZE_NORTH_CLEAR 0
#define MAZE_EAST_CLEAR  1
#define MAZE_SOUTH_CLEAR 2
#define MAZE_WEST_CLEAR  3
#define MAZE_TARGET      4
#define MAZE_WALL        5

#define MAZE_EDGE        0x10

#define MAZE_NEIGHBOURS 0b001111

namespace maze {

using std::vector;
using std::bitset;

typedef std::bitset<MAZE_DATA_BITS> maze_data_t;

class Maze {
 public:
  explicit Maze(std::string const&);

  void print();

 protected:
  void calculate_neighbours();

  vector<vector<maze_data_t>> grid;
  vector<std::size_t> dimension;
  vector<vector<bitset<4>>> wall_view();

  static std::map<char, std::string> const characters;
};

} // namespace maze

#endif  // CODEWARS_MAZE_MAZE_H_
