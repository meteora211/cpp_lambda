#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <typename C, typename T = typename C::value_type>
std::unordered_map<T, int> count_words(const C &collection) {
  std::unordered_map<T, int> results;
  for (auto &item : collection) {
    results[item]++;
  }
  return results;
}

template <typename C,
          typename T1 = std::remove_cv_t<typename C::value_type::first_type>,
          typename T2 = std::remove_cv_t<typename C::value_type::second_type>>
          std::vector<std::pair<T2, T1>> reverse_pair(const C &items) {
  std::vector<std::pair<T2, T1>> results(items.size());

  std::transform(items.cbegin(), items.cend(), results.begin(),
                 [](const std::pair<T1, T2> &item) {
                   return std::make_pair(item.second, item.first);
                 });
  return results;
}

int main() {
  std::vector<std::string> words{std::string("The"),    std::string("Farm"),
                                 std::string("from"),   std::string("the"),
                                 std::string("Animal"), std::string("Farm")};
  for (auto &&item : reverse_pair(count_words(words))) {
    std::cout << item.first << " " << item.second << std::endl;
  }

}
