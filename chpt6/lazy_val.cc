#include <iostream>
#include <optional>
#include <functional>
#include <string>
#include <mutex>

template<typename F>
class lazy_val {
public:
  lazy_val(F function) : m_function(function) {}
  lazy_val(lazy_val&& rhs) : m_function(std::move(rhs.m_function)) {}
private:
  F m_function;
  mutable std::optional<decltype(m_function())> m_result;
  mutable std::mutex m_lock;
public:
  operator decltype(m_function()) () const {
    std::scoped_lock lock{m_lock};
    if (!m_result) {
      m_result = std::invoke(m_function);
    }
    return *m_result;
  }
};

template <typename F>
auto make_lazy_val(F&& function) {
  return lazy_val(std::forward<F>(function));
}

struct _make_lazy_val_helper {
  template<typename F>
  auto operator - (F&& function) {
    return lazy_val<F>(function);
  }
} make_lazy_val_helper;

#define lazy make_lazy_val_helper - [=]

int get_anwser() {
  std::cout << "get the anwser" << std::endl;
  return 42;
}

int main() {
  int number = 6;
  auto val = lazy {
    std::cout << "Calculating the anwser..." << std::endl;
    std::cout << "The number is: " << number << std::endl;
    return 42;
  };

  std::cout << "lazy value defined" << std::endl;
  std::cout << val << std::endl;

  auto lazy_get = make_lazy_val(get_anwser);
  std::cout << "lazy anwser defined" << std::endl;
  int anwser = static_cast<int>(lazy_get);
  std::cout << "anwser is: " << anwser << std::endl;
}
