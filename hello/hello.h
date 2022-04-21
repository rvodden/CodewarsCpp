#if defined(_WIN32)
#if defined(EXPORTING_MYMATH)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
#else  // non windows
#define DECLSPEC
#endif

#include <map>
#include <string>
#include <vector>

namespace hello {

struct PeakData {
  std::vector<int> pos;
  std::vector<int> peaks;
};

std::string DECLSPEC hello(void);
int DECLSPEC square_digits(int);
int DECLSPEC getCount(const std::string&);
int DECLSPEC countSmileys(const std::vector<std::string>&);
std::string DECLSPEC to_camel_case(const std::string&);
int countBits(const unsigned long long& num);
int digital_root( int n );
std::map<char, unsigned> countLetters(const std::string& string);
long zeros(const long&);
PeakData pick_peaks(std::vector<int> const&);
int maxSequence(std::vector<int> const&);

std::string range_extraction(std::vector<int> const&);


}  // namespace hello