#include <bits/stdc++.h>
using namespace std;
vector<vector<char>> sky(6561, vector<char>(6561, ' '));

void fill(int a, int b, int size) {
    if (size == 3) {
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) sky[a + i][b + j] = '*';
        sky[a + 1][b + 1] = ' ';
        return;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != 1 || j != 1) fill(a + i * (size / 3), b + j * (size / 3), size / 3);
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    fill(0, 0, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << sky[i][j];
        cout << "\n";
    }
}