#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "Person.h"

bool is_female(const Person &p) { return p.gen() == Person::female; }

bool is_not_female(const Person &p) { return !is_female(p); }

std::string get_person_name(const Person &p) { return p.name(); }

// Option1: 2 stage to execute
std::vector<std::string> name_for_two_stage(const std::vector<Person> &people) {
  std::vector<Person> females;
  std::copy_if(people.cbegin(), people.cend(), std::back_inserter(females),
               is_female);

  std::vector<std::string> names(females.size());

  std::transform(females.cbegin(), females.cend(), names.begin(),
                 get_person_name);
  return names;
}

// Option2: for loop
template <typename FilterFunction>
std::vector<std::string> name_for_loop(const std::vector<Person> &people,
                                       FilterFunction filter) {
  std::vector<std::string> names;
  for (const auto &p : people) {
    if (filter(p)) {
      names.push_back(get_person_name(p));
    }
  }
  return names;
}

// Option3: recursive with tail call optimization(TCO)
template <typename Iterator, typename FilterFunction>
std::vector<std::string> tco_helper(Iterator people_begin, Iterator people_end,
                                    FilterFunction filter,
                                    std::vector<std::string> pre_collected) {
  if (people_begin == people_end) {
    return pre_collected;
  } else {
    const auto head = *people_begin;
    if (filter(head)) {
      pre_collected.push_back(get_person_name(head));
    }
  }
  return tco_helper(people_begin + 1, people_end, filter,
                    std::move(pre_collected));
}

template <typename FilterFunction>
std::vector<std::string> name_for_tco(const std::vector<Person> &people,
                                      FilterFunction filter) {
  return tco_helper(people.cbegin(), people.cend(), filter, {});
}

// Option4: use accumulate to reduce names
template <typename FilterFunction>
std::vector<std::string> name_for_reduce(const std::vector<Person> &people,
                                         FilterFunction filter) {
  auto append_name_if = [&](std::vector<std::string> pre_collected, const Person& p) -> std::vector<std::string> {
    if (filter(p)) {
      pre_collected.push_back(get_person_name(p));
    }
    return pre_collected;
  };
  return std::accumulate(people.cbegin(),
                         people.cend(),
                         std::vector<std::string>{},
                         append_name_if);
}

int main() {
  std::vector<Person> people{
      {"David", "Doe", Person::male, 20},
      {"Jane", "Doe", Person::female, 20},
      {"Martha", "Doe", Person::female, 20},
      {"Peter", "Doe", Person::male, 20},
      {"Rose", "Doe", Person::female, 20},
      {"Tom", "Doe", Person::male, 20},
  };

  auto two_stage_names = name_for_two_stage(people);
  for (const auto &name : two_stage_names) {
    std::cout << name << "\n";
  }
  std::cout << "------------\n";

  auto for_loop_names = name_for_loop(people, is_female);
  for (const auto &name : for_loop_names) {
    std::cout << name << "\n";
  }
  std::cout << "------------\n";

  auto tco_names = name_for_tco(people, is_female);
  for (const auto &name : tco_names) {
    std::cout << name << "\n";
  }
  std::cout << "------------\n";

  auto reduce_names = name_for_reduce(people, is_female);
  for (const auto &name : tco_names) {
    std::cout << name << "\n";
  }
}
