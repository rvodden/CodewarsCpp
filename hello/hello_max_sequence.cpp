#include <vector>

#include "hello.h"

namespace hello {

int maxSequence(std::vector<int> const& v) {
  int const size = v.size();

  if (size == 0) {
    return 0;
  }

  int max = 0;
  for (int i = 0; i < size; i++) {
    for(int j = i; j < size; j++) {
     int value = 0;
     for (int k = i; k <= j; k++) {
       value += v[k];
     }
     max = std::max(max, value);
    }
  }

  return max;
}

} // namespace hello