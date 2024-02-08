#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> floors(128, vector<int>(128, 0));
int num = 1;

void solution(int stx, int sty, int sz, int px, int py) {
    if (sz == 2) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (stx + i != px || sty + j != py) {
                    floors[sty + j][stx + i] = num;
                }
            }
        }
        ++num;
        return;
    }
    int xper = (px - stx) / (sz / 2), yper = (py - sty) / (sz / 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (j != xper || i != yper) {
                floors[sty + (sz / 2) - 1 + i][stx + (sz / 2) - 1 + j] = num;
            }
        }
    } ++num;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (j != xper || i != yper) {
                solution(stx + (sz / 2) * j, sty + (sz / 2) * i, sz / 2, stx + (sz / 2) - 1 + j, sty + (sz / 2) - 1 + i);
            } else {
                solution(stx + (sz / 2) * xper, sty + (sz / 2) * yper, sz / 2, px, py);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int K; cin >> K;
    int x, y; cin >> x >> y;
    int k = 1; for (int i = 0; i < K; ++i) k *= 2;
    solution(0, 0, k, x - 1, k - y);
    floors[k - y][x - 1] = -1;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << floors[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}