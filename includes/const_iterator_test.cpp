// Copyright 2022 kohkubo

#include <iostream>
#include <vector>
#include "vector.hpp"

#define FT ft

int main() {
    int array[] = {1, 2, 3, 4, 5};
    FT::vector<int> v(array, array + 5);
    std::cout << "v.size() = " << v.size() << std::endl;
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    // test erase
    std::cout << "========== erase ===========" << std::endl;
    FT::vector<int>::iterator it = v.begin();
    std::cout << "v.erase(it)" << std::endl;
    FT::vector<int>::iterator it2 = v.erase(it);
    std::cout << "v.size() = " << v.size() << std::endl;
    std::cout << "it2 = " << *it2 << std::endl;
    std::cout << "v.erase(it2)" << std::endl;
    FT::vector<int>::iterator it3 = v.erase(it2);
    std::cout << "v.size() = " << v.size() << std::endl;
    std::cout << "it3 = " << *it3 << std::endl;

    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
