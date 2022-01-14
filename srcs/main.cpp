#include "type_traits.hpp"
#include <iostream>

int main()
{
    std::cout << ft::is_integral<int>::value << std::endl;
    std::cout << ft::is_integral<unsigned int>::value << std::endl;

    ft::integral_constant<bool, true> test;
    std::cout << test.value << std::endl;
    bool test2 = static_cast<bool>(test);
    bool test3 = (bool)test;
    std::cout << test2 << std::endl;
    std::cout << test3 << std::endl;
    return 0;
}
