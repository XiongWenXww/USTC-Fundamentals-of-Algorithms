#include<iostream>
#include<string.h>
#include<map>
#define N 1000

using namespace std;

int main() {
    int result[N], num, n = 0;
    map<string, int> db;     // database Êý¾Ý¿â

    char c[9] = { 0 };
    char name[9] = { 0 };
    char c1[7] = { 'I','N','S','E','R','T' };
    char c2[5] = { 'F','I','N','D' };
    char c3[5] = { 'E','X','I','T' };

    scanf_s("%s", c, 9);
    while (true) {
        if (strcmp(c, c3) == 0) {
            break;
        }
        
        if (strcmp(c, c1) == 0) {
            scanf_s("%d", &num);
            scanf_s("%s", name, 9);
            db[name] = num;
        }
        else if(strcmp(c, c2) == 0) {
            scanf_s("%s", name, 9);
            if (db.find(name) == db.end()) {
                result[n] = -1;
            }
            else {
                result[n] = db[name];
            }
            ++n;
        }

        scanf_s("%s", c, 9);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d\n", result[i]);
    }
}