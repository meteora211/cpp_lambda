#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#include "Person.h"

bool is_female(const Person& p) {
  return p.gen() == Person::female;
}

bool is_not_female(const Person& p) {
  return !is_female(p);
}

std::string get_person_name(const Person& p) {
  return p.name();
}

int main() {
  std::vector<Person> people {
    {"David", "Doe", Person::male, 20 },
    {"Jane", "Doe", Person::female, 20 },
    {"Martha", "Doe", Person::female, 20 },
    {"Peter", "Doe", Person::male, 20 },
    {"Rose", "Doe", Person::female, 20 },
    {"Tom", "Doe", Person::male, 20 },
  };
  std::vector<Person> females;

  std::copy_if(people.cbegin(),
               people.cend(),
               std::back_inserter(females),
               is_female);

  std::vector<std::string> names(females.size());

  std::transform(females.cbegin(),
                 females.cend(),
                 names.begin(),
                 get_person_name);

  for (const auto& name: names) {
    std::cout << name << "\n";
  }
}
