#if defined(_WIN32)
#  if defined(EXPORTING_MYMATH)
#    define DECLSPEC __declspec(dllexport)
#  else
#    define DECLSPEC __declspec(dllimport)
#  endif
#else // non windows
#  define DECLSPEC
#endif

namespace hello {
    std::string DECLSPEC hello();
    int DECLSPEC square_digits(int);
    int DECLSPEC getCount(std::string);
    int DECLSPEC countSmileys(std::vector<std::string>);
}