#include <iostream>
#include "generatePoints.h"
using namespace std;


int main() {
    int n = 100000;
    generateRandomPoints(n);
    printf("%d 个随机不重复的点已保存到 random_points_%d.txt 文件中。\n", n, n);
    return 0;
}
