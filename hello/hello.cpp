#include <sstream>
#include <vector>
#include "hello.h"


int hello::square_digits(int num) {
    std::stringstream ss;
    for (char c : std::to_string(num)) {
        int x = c - '0';
        ss << x*x;
    }
    ss >> num;
    return num;
}

int hello::getCount(std::string inputStr) {
    int num_vowels = 0;
    for(char c : inputStr) {
        switch(c) {
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

int validateFeature(char feature, const std::string& validFeatures) {
    int validFeature = 0;
    for (char f : validFeatures) {
        if (f == feature) validFeature++;
    }
    return validFeature;
}

int hello::countSmileys(std::vector<std::string> arr) {
    int smiles = 0;
    char eye, nose, mouth;

    std::string validEyes = ";:";
    std::string validNoses = "-~";
    std::string validMouths = ")D";

    for(std::string potentialSmile : arr) {
        switch(potentialSmile.length()) {
            case 2: {
                eye = potentialSmile[0];
                nose = '-'; //default to a valid smile
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

        if ( validateFeature(eye, validEyes) &&
                validateFeature(nose, validNoses) &&
                validateFeature(mouth, validMouths) ) {
            smiles++;
        }
    }
    return smiles;
}

// private functions


