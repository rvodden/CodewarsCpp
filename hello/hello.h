#if defined(_WIN32)
#if defined(EXPORTING_MYMATH)
#define DECLSPEC __declspec(dllexport)
#else
#define DECLSPEC __declspec(dllimport)
#endif
#else  // non windows
#define DECLSPEC
#endif

#include <string>

namespace hello {

std::string DECLSPEC hello(void);
int DECLSPEC square_digits(int);
int DECLSPEC getCount(const std::string&);
int DECLSPEC countSmileys(const std::vector<std::string>&);
std::string DECLSPEC to_camel_case(const std::string&);

}  // namespace hello