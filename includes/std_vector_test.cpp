#include <iostream>
#include <vector>

int main()
{
    std::cout << "========== std::vector ===========" << std::endl;
    std::vector<int> std_v(10);
    std::cout << "std_v.size() = " << std_v.size() << std::endl;
    std::cout << "std_v.capacity() = " << std_v.capacity() << std::endl;
    std::cout << "std_v.empty() = " << std_v.empty() << std::endl;
    std::cout << "========== std_v.push_back(1) ===========" << std::endl;
    std_v.push_back(100);
    std::cout << "std_v.push_back(100)" << std::endl;
    std_v.push_back(200);
    std::cout << "std_v.push_back(200)" << std::endl;
    std_v.push_back(300);
    std::cout << "std_v.push_back(300)" << std::endl;
    for (size_t i = 0; i < std_v.size(); ++i)
        std::cout << std_v[i] << " ";
    std::cout << std::endl;
    std::cout << "std_v.size() = " << std_v.size() << std::endl;
    std::cout << "std_v.capacity() = " << std_v.capacity() << std::endl;
    std::cout << "std_v.empty() = " << std_v.empty() << std::endl;
    std::cout << "std_v.begin() = " << *std_v.begin() << std::endl;
    std::cout << "std_v.end() = " << *--std_v.end() << std::endl;

    std::cout << "========== copy constructor ===========" << std::endl;
    std::vector<int> std_v2(std_v);
    std::cout << "std_v2.size() = " << std_v2.size() << std::endl;
    std::cout << "std_v2.capacity() = " << std_v2.capacity() << std::endl;
    std::cout << "std_v2.empty() = " << std_v2.empty() << std::endl;
    std::cout << "std_v2.begin() = " << *std_v2.begin() << std::endl;
    std::cout << "std_v2.end() = " << *--std_v2.end() << std::endl;

    // iterator
    std::cout << "========== iterator ===========" << std::endl;
    std::vector<int>::iterator it = std_v.begin();
    return 0;
}
