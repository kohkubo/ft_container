#include <iostream>
#include <vector>
#include "vector.hpp"
#include <time.h>
#include <map>

int main()
{
    std::cout << "clock():\n";
    for (int i = 0; i < 10; ++i) {
        std::map<int, int> v;         // int 型動的配列
        const int N = 4194304;    //  10万回
        for (int i = 0; i < N; ++i) {
            v.insert(std::make_pair(i, i));              // 末尾に i を追加
        }
        clock_t start = clock();    // スタート時間
        for (int i = 0; i < N; ++i) {
            v.erase(i);                                  // i の要素を削除
        }
        clock_t end = clock();     // 終了時間
        std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC << "sec.\n";
    }
    return 0;
}
