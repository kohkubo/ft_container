// Copyright (c) 2022 kohkubo

#include <iostream>

void pass_by_value(int* p) {
  // Allocate memory for int and store the address in p
  p = new int;
  *p = 10;
}

void pass_by_reference(int*& p) { p = new int; }

int  main() {
  int* p1 = new int(1);
  int* p2 = new int(2);


  pass_by_value(p1);
  pass_by_reference(p2);

  std::cout << "p1: " << *p1 << std::endl;
  std::cout << "p2: " << *p2 << std::endl;
  return 0;
}
