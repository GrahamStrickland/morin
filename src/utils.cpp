#include <iostream>

#include "utils.h"

void print_heading(std::string heading) {
  std::string border = "";
  border.append(heading.length() + 1, '=');
  std::cout << border << '\n' << heading << ':' << '\n' << border << std::endl;
}
