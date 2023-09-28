#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

using namespace std;

int main() {
  int count = 0;
  vector<string> words {"duck", "duck", "go"};

  // MUTABLE lambda
  for_each(
    words.cbegin(),
    words.cend(),
    // NOTE: captured variables are default const
    [count](const string& word) mutable {
      cout << "process " << count++ << "th word: " << word << endl;
    }
  );

  // MOVE capture
  auto ptr = make_unique<int>(42);
  auto fun1 = [ptr=std::move(ptr)]() mutable {
    ptr.reset(new int(0));
    return std::move(ptr);
  };

  auto ptr_reset = fun1();
  cout << *ptr_reset << endl;

}

