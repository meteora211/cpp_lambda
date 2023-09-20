#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int count_lines(const string& file) {
  ifstream in(file);
  return std::count(
    std::istreambuf_iterator<char>(in),
    std::istreambuf_iterator<char>(),
    '\n'
  );
}

vector<int> count_lines_in_files_declarative(const vector<string> &files) {
  vector<int> results(files.size());
  string line;
  // for (const string &file : files) {
  //   results.push_back(count_lines(file));
  // }
  transform(files.cbegin(), files.cend(),
            results.begin(),
            count_lines);
  return results;
}

int main() {
  auto cur_path = filesystem::current_path();
  auto file_name = "chp1/test_in_file0";
  auto file_path = cur_path / file_name;
  cout << count_lines_in_files_imperative({file_path, file_path}) << endl;
  cout << count_lines_in_files_declarative({file_path, file_path}) << endl;
}
