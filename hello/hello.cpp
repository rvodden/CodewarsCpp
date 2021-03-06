#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bitset>
#include <climits>

#include "hello.h"

int hello::square_digits(int num) {
  std::stringstream sstream;
  for (char chr : std::to_string(num)) {
    int x = chr - '0';
    sstream << x * x;
  }
  sstream >> num;
  return num;
}

int hello::getCount(const std::string& inputStr) {
  int num_vowels = 0;
  for (char chr : inputStr) {
    switch (chr) {
      case 'a':
      case 'e':
      case 'i':
      case 'o':
      case 'u': {
        num_vowels++;
        break;
      }
      default: {
        break;
      }
    }
  }
  return num_vowels;
}

bool validateFeature(char feature, const std::string& validFeatures) {
  bool validFeature = false;
  for (char feat : validFeatures) {
    if (feat == feature) {
      validFeature = true;
    }
  }
  return validFeature;
}

int hello::countSmileys(const std::vector<std::string>& arr) {
  int smiles = 0;
  char eye;
  char nose;
  char mouth;

  std::string validEyes = ";:";
  std::string validNoses = "-~";
  std::string validMouths = ")D";

  for (std::string potentialSmile : arr) {
    switch (potentialSmile.length()) {
      case 2: {
        eye = potentialSmile[0];
        nose = '-';  // default to a valid smile
        mouth = potentialSmile[1];
        break;
      }
      case 3: {
        eye = potentialSmile[0];
        nose = potentialSmile[1];
        mouth = potentialSmile[2];
        break;
      }
      default:
        continue;
    }

    if (validateFeature(eye, validEyes) && validateFeature(nose, validNoses) &&
        validateFeature(mouth, validMouths)) {
      smiles++;
    }
  }
  return smiles;
}

std::string hello::to_camel_case(const std::string& text) {
  std::string delimiters = "-_";
  std::stringstream stream[delimiters.length() + 1];

  stream[0] << text;
  for (unsigned long idx = 0; idx < delimiters.length(); idx++) { // NOLINT(google-runtime-int)
    bool first_word = true;
    for(std::string words; std::getline(stream[idx], words, delimiters[idx]); ) {
      if (! first_word ) {  // last time through
        words[0] = std::toupper(words[0]);
      }
      stream[idx+1] << words;
      first_word = false;
    }
  }
  return stream[delimiters.length()].str();
}

int hello::countBits(const unsigned long long& num) {
  short const length = CHAR_BIT*sizeof(unsigned long long);
  std::bitset<length> bts = std::bitset<length>(num);
  return bts.count();
};

int hello::digital_root(int n) {
  const int base = 10;
  if (n < base) {
    return n;
  }

  int sum = 0;
  do {
    std::div_t result = std::div(n, base);
    sum += result.rem;
    n = result.quot;
  } while ( n != 0 );

  if (sum >= base) {
    sum = digital_root(sum);
  }

  return sum;
}

std::map<char, unsigned> hello::countLetters(const std::string& string) {
  std::map<char, unsigned> m = {}; // start with empty map
  for (const char&c : string) {
    m[c]++;
  }

  return m;
}

long hello::zeros(const long& n) {
  int const base = 5;
  long k = std::floor(std::log(n) / std::log(base));
  long val = 0;
  for (long i = 1; i <= k; i++) {
    val += std::floor( n / (std::pow(base, i)));
  }
  return val;
}
// private functions
