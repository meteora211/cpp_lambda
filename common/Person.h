#pragma once
#include <string>
#include <iostream>

struct Person {
  enum gender { female, male, other };

  enum output_format { name_only, full_name };

  Person(const std::string& name, const std::string &sur_name, gender g, int age = 0)
      : name_(name), sur_name_(sur_name), gender_(g), age_(age) {}

  std::string name() const {
    return name_;
  }

  std::string sur_name() const {
    return sur_name_;
  }

  gender gen() const {
    return gender_;
  }

  std::string gen_to_str() const {
    switch (gender_) {
      case gender::female:
      return "female";
      case gender::male:
      return "male";
      case gender::other:
      return "other";
    }
  }

  int age() const {
    return age_;
  }

private:
  std::string name_;
  std::string sur_name_;
  gender gender_;
  int age_;
};

inline std::ostream& operator<<(std::ostream& os, const Person& p) {
  return os << "[" << p.name() << "-" << p.sur_name() << "]: \n"
  << "gender: " << p.gen_to_str() << "\n"
  << "age: " << p.age() << "\n";
}
