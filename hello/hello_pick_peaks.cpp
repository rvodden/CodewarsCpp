#include "hello.h"

#include <iostream>

namespace hello {

  PeakData pick_peaks(std::vector<int> const& v) {
    PeakData result;

    for (int const& j : v) {
      std::cout << j;
    }
    std::cout << "\n";

    bool plateau = false;
    std::size_t plateau_start = 0;
    std::size_t i = 0;

    int prev;
    int curr = v[0];
    int next = v[1];

    for(i = 1; i < (v.size() - 1); i++) {
      prev = curr;
      curr = next;
      next = v[i+1];
      // if we are going down hill, skip.
      if ( curr < prev ) {
        continue;
      }

      // if we are on a level, but we got here downwards, skip.
      if ( curr == prev && !plateau ) {
        continue;
      }

      if( curr > next ) {
        result.pos.push_back(plateau ? plateau_start : i);
        result.peaks.push_back(curr);
        plateau = false;
        continue;
      }

      if ( curr == next && ! plateau) {
        plateau_start = i;
        plateau = true;
        continue;
      }

      if ( curr < next ) {
        plateau = false;
      }
    }

    return result;
  }

}