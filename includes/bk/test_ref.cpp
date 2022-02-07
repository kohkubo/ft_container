#include <iostream>

void input(int *a, int *test) {
  *test = *a;
}

int main() {
  int *null = NULL;
  int *&test = null;
  int *a = new int(5);
  input(a, test);
  std::cout << *test << std::endl;
}
