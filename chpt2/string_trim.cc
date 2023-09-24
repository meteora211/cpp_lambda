#include <string>
#include <iostream>
#include <algorithm>

bool is_not_space(char c) {
  return c != ' ';
}

std::string trim_left(std::string str) {
  str.erase(
    str.begin(),
    std::find_if(str.begin(), str.end(), is_not_space)
  );
  return str;
}

std::string trim_right(std::string str) {
  str.erase(
    std::find_if(str.rbegin(), str.rend(), is_not_space).base(),
    str.end()
  );
  return str;
}

std::string trim(std::string str) {
  return trim_left(trim_right(str));
}

int main() {
  std::cout << trim("    hello world    ") << std::endl;
}
