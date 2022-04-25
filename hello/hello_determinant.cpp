//
// Created by Richard Vodden on 21/04/2022.
//
#include <numeric>
#include <stdexcept>

#include "hello.h"

using std::vector;

static inline long long _determinant(vector<vector<long long>> const& m,
                                     vector<std::size_t> const& is,
                                     vector<std::size_t> const& js);

long long hello::determinant(vector<vector<long long>> m) {
  if (m.empty())
    throw std::domain_error(
        "A determinant cannot be calculated on an empty matrix.");
  if (m.size() != m.at(0).size())
    throw std::domain_error(
        "A determinant is only defined for a square matrix.");
  if (m.size() == 1) return m.at(0).at(0);

  std::vector<std::size_t> include_idx(m.size());
  std::iota(include_idx.begin(), include_idx.end(), 0);

  return _determinant(m, include_idx, include_idx);
}

static inline long long _determinant(vector<vector<long long>> const& m,
                                     vector<std::size_t> const& is,
                                     vector<std::size_t> const& js) {
  size_t end = is.size();

  if (end == 2)
    return m.at(is.at(0)).at(js.at(0)) * m.at(is.at(1)).at(js.at(1)) -
           m.at(is.at(1)).at(js.at(0)) * m.at(is.at(0)).at(js.at(1));

  long long determinant = 0;
  short sign = 1;
  vector<std::size_t> new_is = is;
  new_is.erase(new_is.begin());

  for (size_t j = 0; j < js.size(); j++) {
    vector<std::size_t> new_js = js;
    new_js.erase(std::next(new_js.begin(), j));
    determinant +=
        sign * m.at(is.at(0)).at(js.at(j)) * _determinant(m, new_is, new_js);
    sign *= -1;
  }
  return determinant;
};
