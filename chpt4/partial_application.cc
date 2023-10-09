#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std::placeholders;

const double PI = std::acos(-1.0);

template <typename Function, typename SecondArgType>
class bind2nd_impl {
public:
  bind2nd_impl(Function func, SecondArgType second_arg)
      : m_function(func), m_second_arg(second_arg) {}

private:
  Function m_function;
  SecondArgType m_second_arg;

public:
  template <typename FirstArgType>
  auto operator()(FirstArgType &&first_arg)
      -> decltype(m_function(std::forward<FirstArgType>(first_arg),
                             m_second_arg)) {
    // -> decltype(auto) {
    return m_function(std::forward<FirstArgType>(first_arg), m_second_arg);
  }
};

// XXX: technically is partial function evaluation not currying.
template<typename Function, typename... Args>
auto partial(Function&& func, Args&&... args) {
  return [=](auto&&... remainArgs) {
    return func(args..., remainArgs...);
  };
}

int add(int a, int b) {
  std::cout << "call add: arg1: " << a << " arg2: " << b << std::endl;
  return a + b;
}

template <typename Function, typename SecondArgType>
bind2nd_impl<Function, SecondArgType> bind2nd(Function &&func,
                                              SecondArgType &&second_arg) {
  return bind2nd_impl<Function, SecondArgType>(
      std::forward<Function>(func), std::forward<SecondArgType>(second_arg));
}

int main() {
  auto bind_func = bind2nd(add, 5);
  std::cout << bind_func(3) << std::endl;

  std::vector<double> degrees {0, 30, 45, 60};
  std::vector<double>radians(degrees.size());
  std::transform(degrees.cbegin(),
                 degrees.cend(),
                 radians.begin(),
                 bind2nd(std::multiplies<double>(),
                         PI / 180));
  for (auto&& r : radians) {
    std::cout << r << " ";
  }
  std::cout << "\n";

  std::cout << std::plus<double>()(1,2) << std::endl;
  auto std_bind = std::bind(std::plus<double>(), 2, 3);
  std::cout << std_bind() << std::endl;

  auto bind_add_ref = std::bind(add, _1, 2);
  std::cout << bind_add_ref(1) << std::endl;
  auto bind_add_ptr = std::bind(&add, 1, _1);
  std::cout << bind_add_ptr(2) << std::endl;
  auto bind_add_rev = std::bind(&add, _2, _1);
  std::cout << bind_add_rev(1, 2) << std::endl;

  auto partial_fun1 = partial(add, 1);
  std::cout << partial_fun1(2) << std::endl;
}
