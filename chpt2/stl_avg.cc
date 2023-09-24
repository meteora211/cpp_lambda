#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

double average_score_ref(const std::vector<int> &scores) {
  int sum = 0;
  for (int score : scores) {
    sum += score;
  }
  return sum / static_cast<double>(scores.size());
}

double average_score_stl(const std::vector<int> &scores) {
  return std::accumulate(scores.cbegin(), scores.cend(), 0) /
         static_cast<double>(scores.size());
}

double average_score_stl_parallel(const std::vector<int> &scores) {
  return std::reduce(std::execution::par, scores.cbegin(), scores.cend(), 0) /
         static_cast<double>(scores.size());
}

double score_product_stl(const std::vector<int> &scores) {
  return std::accumulate(scores.cbegin(),
                         scores.cend(),
                         1,
                         std::multiplies<int>());
}

int main() {
  std::vector<int> scores{1,2,3,4,5,6,7,8,9};
  std::cout << "avg score ref: " << average_score_ref(scores) << "\n"
            << "avg score stl: " << average_score_stl(scores) << "\n"
            << "avg score par: " << average_score_stl_parallel(scores) << "\n"
            << "prd score stl: " << score_product_stl(scores) << "\n";
}
