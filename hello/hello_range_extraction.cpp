//
// Created by Richard Vodden on 21/04/2022.
//
#include <sstream>

#include "hello.h"

std::string hello::range_extraction(std::vector<int> const& v) {
  std::stringstream out;
  std::vector<int>::const_iterator it = v.begin();

  int prev = *it++;
  out << prev;

  for(; it < v.end(); it++){
    if (*it - prev == 1) { // are we in a consecutive situation?
      bool separator_required = true;
      prev = *it;
      while (*++it - prev == 1 && it < v.end()) { // while we're still consecutive and there are numbers
        if (separator_required) {
          out << "-";
          separator_required = false;
        }
        prev = *it; // move to the next number
      }
      if (separator_required) {
        out << ",";
      }
      out << prev; // write out the previous number
      if(it == v.end()) {
        break;
      }
    }
    out << "," << *it; // we're not consecutive so write a comma and then the number
    prev = *it;
  }

  return out.str();
}