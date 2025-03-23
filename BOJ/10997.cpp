#include <bits/stdc++.h>
using namespace std;

char arr[399][401];

int N;

void f(int y1, int y2, int x1, int x2) {
    int n = (x2 - x1 + 3) / 4;
    if (n == 2) {
        for (int i = 0; i < 4 * n - 3; ++i) arr[y1][x1 + i] = '*', arr[y2 - 1][x1 + i] = '*';
        for (int i = 0; i < 3 + 4 * (n - 1); ++i) arr[y1 + i][x1] = '*';
        for (int i = 2; i < 3 + 4 * (n - 1); ++i) arr[y1 + i][x2 - 1] = '*';
        for (int i = 2; i < 3 + 4 * (n - 1) - 2; ++i) arr[y1 + i][x1 + 2] = '*';
        arr[y1 + 2][x2 - 2] = '*';
        return;
    }
    for (int i = x1; i < x2; ++i) arr[y1][i] = '*', arr[y2 - 1][i] = '*';
    for (int i = y1; i < y2; ++i) arr[i][x1] = '*';
    for (int i = y1 + 2; i < y2; ++i) arr[i][x2 - 1] = '*';
    arr[y1 + 2][x2 - 2] = '*';
    f(y1 + 2, y2 - 2, x1 + 2, x2 - 2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    if (N == 1) {
        cout << "*";
        return 0;
    }
    int n = 4 * N - 1, m = 4 * N - 3;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) arr[i][j] = ' ';
    f(0, n, 0, m);
    for (int i = 0; i < n; ++i) {
        if (i == 1) {
            cout << "*\n";
            continue;
        }
        for (int j = 0; j < m; ++j) cout << arr[i][j];
        cout << '\n';
    }
}