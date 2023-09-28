#include <iostream>

using namespace std;

int ask() { return 42; }

typedef decltype(&ask) func_ptr;
// typedef decltype(ask) *func_ptr;

struct convert_to_func_ptr {
  operator func_ptr() const { return ask; }
};

int main() {
  cout << "ask: " << (void *)ask << " &ask: " << (void *)&ask << endl;

  auto ask_ptr = &ask;
  cout << ask_ptr() << endl;

  auto &ask_ref = ask;
  cout << ask_ref() << endl;

  // NOTE: Function-to-pointer conversion:
  // https://en.cppreference.com/w/cpp/language/implicit_conversion#Function_to_pointer
  // An lvalue of function type can be implicitly converted to a prvalue pointer
  // to that function. This does not apply to non-static member functions
  // because lvalues that refer to non-static member functions do not exist.
  func_ptr fp1 = ask;
  func_ptr fp2 = &ask;
  cout << "fp1: " << (void *)fp1 << " " << fp1() << endl;
  cout << "fp2: " << (void *)fp2 << " " << fp2() << endl;

  convert_to_func_ptr cfp;
  cout << cfp() << endl;
}
