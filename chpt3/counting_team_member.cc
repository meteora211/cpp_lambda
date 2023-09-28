#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "Person.h"

bool older_than_42(const Person& p) {
  return p.age() > 42;
}

class older_than {
public:
  older_than(int age) : age_(age) {}
  // NOTE: template operator function instead of template class definiation.
  template<typename T>
  bool operator()(T&& object) const {
    return std::forward<T>(object).age() > age_;
  }
private:
  int age_;
};

class Company {
public:
  explicit Company(const std::vector<Person>& p) : employee(p) {}
  std::string team_name_for(const Person& p) {
    if (p.age() > 20) {
      return "team1";
    } else {
      return "team2";
    }
  }
  int count_team_members(const std::string& team_name) {
    return std::count_if(
      employee.cbegin(),
      employee.cend(),
      [&](const Person& p){
        return team_name_for(p) == team_name;
      }
    );
  }
private:
  std::vector<Person> employee;
};

int main() {
  std::vector<Person> people {
    {"David", "Doe", Person::male, 20 },
    {"Jane", "Doe", Person::female, 40 },
    {"Martha", "Doe", Person::female, 50 },
    {"Peter", "Doe", Person::male, 10 },
    {"Rose", "Doe", Person::female, 60 },
    {"Tom", "Doe", Person::male, 30 },
  };

  std::cout << std::count_if(people.cbegin(),
                people.cend(),
                older_than_42) << std::endl;

  std::cout << std::count_if(people.cbegin(),
                people.cend(),
                older_than(42)) << std::endl;

  Company company(people);
  std::cout << "team1 in company: " << company.count_team_members("team1") << std::endl;
}
