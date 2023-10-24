#include "generatePoints.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point{
    int x;
    int y;
};
#define MAX_X 1000
#define MAX_Y 1000

int hashIt(int x, int y) {
    return x * (MAX_Y + 1) + y;
}

int isPointInHashTable(int* hashTable, struct Point p) {
    int index = hashIt(p.x, p.y);
    return hashTable[index];
}

void generateRandomPoints(int n) {
    // 使用 sprintf 构建文件名
    char filename[20];
    sprintf(filename, "random_points_%d.txt", n);

    FILE* file = fopen(filename, "w");
    if (file == nullptr){
        printf("文件打开失败");
        return;
    }

    srand(time(nullptr));
    int* hashTable = (int*) calloc((MAX_X+1)*(MAX_Y+1), sizeof(int));
    if (hashTable == nullptr) {
        printf("创建hashTable失败");
        fclose(file);
        return;
    }

    struct Point p;

    while(n > 0) {
        p.x = rand() % (MAX_X + 1);
        p.y = rand() % (MAX_Y + 1);

        if (!isPointInHashTable(hashTable, p)) {
            hashTable[hashIt(p.x, p.y)] = 1;
            fprintf(file, "%d %d\n", p.x, p.y);
            n--;
        }

    }

    fclose(file);
    free(hashTable);
}