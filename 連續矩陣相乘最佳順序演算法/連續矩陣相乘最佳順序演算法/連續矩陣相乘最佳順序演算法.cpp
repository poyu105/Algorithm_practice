/*
* 此為"連續矩陣相乘最佳順序演算法"

輸入:
第一行為矩陣的數量𝑛（2≤𝑛≤9)。第二行是𝑛+1個以空白隔開的整數值，代表陣列d的值，其中d[i-1] x d[i] 表示第𝑖個矩陣的維度。
譬如以下範例的輸入方式：
6
5 2 3 4 6 7 8
輸出:
輸出最佳解。譬如。前述的輸入應印出最佳解如下：Optimal Solution: A1((((A2A3)A4)A5)A6)
*/
#include <iostream>
#include <algorithm>
using namespace std;
void order(int P[10][10], int i, int j) {
    if (i == j) {
        cout << "A" << i;
    }
    else {
        int k = P[i][j];
        cout << "(";
        order(P, i, k);
        order(P, k + 1, j);
        cout << ")";
    }
}
int main() {
    int n, d[10] = { 0 };
    cin >> n;
    for (int i = 0; i < n + 1; i++) {
        cin >> d[i];
    }
    int M[10][10] = { 0,0 }, P[10][10] = { 0,0 };
    for (int i = 0; i < n; i++) {
        M[i][i] = 0;
        P[i][i] = 0;
    }
    for (int diagonal = 1; diagonal <= n - 1; diagonal++) {
        for (int i = 1; i <= n - diagonal; i++) {
            int j = i + diagonal;
            int minCount = 9999;
            for (int k = i; k <= j - 1; k++) {
                minCount = min((M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]), minCount);
                if (M[i][j] == minCount) {
                    continue;
                }
                M[i][j] = minCount;
                P[i][j] = k;
            }
        }
    }
    order(P, 1, n);
}