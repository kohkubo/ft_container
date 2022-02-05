#include <iostream>
#include <vector>
#include "vector.hpp"
#include <time.h>

int main()
{
    std::cout << "clock():\n";
    for (int i = 0; i < 10; ++i) {
        ft::vector<int> v;         // int 型動的配列
        clock_t start = clock();    // スタート時間
        const int N = 1000;    //  10万回
        for (int i = 0; i < N; ++i) {
            v.push_back(i);              // 末尾に i を追加
        }
        clock_t end = clock();     // 終了時間
        std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
    }
    getchar();
    return 0;
}
