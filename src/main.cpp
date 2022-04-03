#include <iostream>

#include "config.h"
#include "hello.h"

int main(int argc, char** argv) {
  // Report Version
  std::cout << "Version " << TEMPLATE_VERSION_MAJOR << "."
            << TEMPLATE_VERSION_MINOR << "." << TEMPLATE_VERSION_PATCH
            << std::endl;

  return 0;
}