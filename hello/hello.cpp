#include "hello.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <locale>

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
  for (unsigned long idx = 0; idx < delimiters.length(); idx++) {
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

// private functions
