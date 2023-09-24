#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>
// NOTE: some features in std::ranges requires c++23. Use range-v3 instead.
// #include <ranges>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;
namespace filesystem = std::filesystem;

// helper function
auto &operator<<(auto &out, const vector<int> &v) {
  out << "{ ";
  for (int e : v)
    out << e << ' ';
  return out << "}";
}

vector<int> count_lines_in_files_imperative(const vector<string> &files) {
  vector<int> results;
  string line;
  for (const string &file : files) {
    int line_count = 0;
    ifstream in(file);
    if (in.is_open()) {
      while (getline(in, line)) {
        ++line_count;
      }
    }
    results.push_back(line_count);
  }
  return results;
}

int count_lines(const string &file) {
  ifstream in(file);
  return std::count(std::istreambuf_iterator<char>(in),
                    std::istreambuf_iterator<char>(), '\n');
}

vector<int> count_lines_in_files_declarative(const vector<string> &files) {
  vector<int> results(files.size());
  // option-1: for-loop
  // for (const string &file : files) {
  //   results.push_back(count_lines(file));
  // }

  // option-2: std transform
  // transform(files.cbegin(), files.cend(),
  //           results.begin(),
  //           count_lines);
  // return results;

  // option-3: ranges
  return files | ranges::views::transform(count_lines) |
         ranges::to<vector<int>>();
}

int main() {
  auto cur_path = filesystem::current_path();
  auto file_name = "chp1/test_in_file0";
  auto file_path = cur_path / file_name;
  cout << count_lines_in_files_imperative({file_path, file_path}) << endl;
  cout << count_lines_in_files_declarative({file_path, file_path}) << endl;
}
