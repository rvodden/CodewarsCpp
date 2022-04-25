#include <string>
#include <vector>
#include <bitset>

#include <map>

#ifndef CODEWARS_MAZE_MAZE_H_
#define CODEWARS_MAZE_MAZE_H_

#define MAZE_DATA_BITS   6
#define MAZE_VIEW_BITS   5

#define MAZE_NORTH_CLEAR 0
#define MAZE_EAST_CLEAR  1
#define MAZE_SOUTH_CLEAR 2
#define MAZE_WEST_CLEAR  3
#define MAZE_TARGET      4
#define MAZE_WALL        5

#define MAZE_EDGE        4

#define MAZE_NEIGHBOURS 0b001111

namespace maze {

using std::vector;
using std::bitset;

typedef std::bitset<MAZE_DATA_BITS> maze_data_t;
typedef std::bitset<MAZE_VIEW_BITS> maze_view_t;

class Maze {
  friend class MazePrinter;

 public:
  explicit Maze(vector<vector<maze_data_t>>& grid) : grid(grid) {};
  ~Maze() { delete &grid; };

  bool path_finder();
  int  shortest_path();

 private:
  bool _path_finder(vector<std::size_t> const&, vector<vector<bool>>&);
  unsigned int _shortest_path(vector<vector<bool>>&, vector<vector<unsigned int>>&);

  vector<vector<maze_data_t>>& grid;
};

class MazeBuilder {
 public:
  static Maze build(std::string);

 private:
  static void calculate_neighbours(vector<vector<maze_data_t>>&);
};

class MazePrinter {
 public:
  static void print(Maze const&);

 private:
  static vector<vector<maze_view_t>> wall_view(vector<vector<maze_data_t>> const&, vector<std::size_t> const&);
  static std::map<char, std::string> const characters;
};
} // namespace maze

#endif  // CODEWARS_MAZE_MAZE_H_
