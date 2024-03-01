#include <vector>
#include <range/v3/all.hpp>
#include <Person.h>
#include <string>


bool is_female(const Person &p) { return p.gen() == Person::female; }
std::string name(const Person& p) {return p.name();}

int main() {
  std::vector<Person> people{
      {"David", "Doe", Person::male, 20},
      {"Jane", "Doe", Person::female, 20},
      {"Martha", "Doe", Person::female, 20},
      {"Peter", "Doe", Person::male, 20},
      {"Rose", "Doe", Person::female, 20},
      {"Tom", "Doe", Person::male, 20},
  };

  std::vector<std::string> names = people | ranges::views::filter(is_female) | ranges::views::transform(name) | ranges::to<std::vector<std::string>>();

  for (auto&& n: names) {
    std::cout << n << std::endl;
  }

}
