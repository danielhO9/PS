#include <bits/stdc++.h>
using namespace std;
int answer = 0;

// 잘라야 하는 곳 - 불순물이 있는 곳
// 이전과는 다른 방향으로 잘라야 함
// 석판에는 보석이 하나만, 불순물은 없이
// 자르는 방향에 보석이 있으면 안됨

int N; vector<vector<int>> plate(20, vector<int>(20, 0));

int divide(int minx, int miny, int maxx, int maxy, int way) {
    int ret = 0, gem = 0, trash = 0;
    for (int i = miny; i <= maxy; ++i) {
        for (int j = minx; j <= maxx; ++j) {
            if (plate[i][j] == 1) ++trash;
            else if (plate[i][j] == 2) ++gem;
        }
    }
    if (trash == 0) {
        if (gem == 1) ret = 1;
        else ret = 0;
    } else {
        vector<bool> xset(20, 0), yset(20, 0);
        for (int i = miny; i <= maxy; ++i) {
            for (int j = minx; j <= maxx; ++j) {
                if (plate[i][j] == 1) {
                    if (way == -1 || way == 0) {
                        bool yaxis = true;
                        for (int k = miny; k <= maxy; ++k) {
                            if (plate[k][j] == 2) { yaxis = false; break; }
                        }
                        if (yaxis && yset[j] == false && j != minx && j != maxx) { ret += divide(minx, miny, j - 1, maxy, 1) * divide(j + 1, miny, maxx, maxy, 1); yset[j] = true;}
                    }
                    if (way == -1 || way == 1) {
                        bool xaxis = true;
                        for (int k = minx; k <= maxx; ++k) {
                            if (plate[i][k] == 2) { xaxis = false; break; }
                        }
                        if (xaxis && xset[i] == false && i != miny && i != maxy) { ret += divide(minx, miny, maxx, i - 1, 0) * divide(minx, i + 1, maxx, maxy, 0); xset[i] = true; }
                    }
                }
            }
        }
    }
    // cout << minx << " " << miny << " " << maxx << " " << maxy << " " << gem << " " << trash << " " << ret << endl;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> plate[i][j];
    int answer = divide(0, 0, N - 1, N - 1, -1);
    if (answer == 0) answer = -1;
    cout << answer;
    return 0;
}