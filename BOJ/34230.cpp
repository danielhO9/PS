#include <bits/stdc++.h>
using namespace std;

int N;
int A[5000];
int tree[5000][4096][2];
int pmn[4096], smn[4096];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) for (int j = 0; j < 4096; ++j) for (int k = 0; k < 2; ++k) tree[i][j][k] = N + 1;
    
    // 0: increase, 1: decrease
    for (int i = 0; i < N; ++i) for (int j = 0; j < 2; ++j) {
        if (i != 0) {
            for (int k = 0; k < 4096; ++k) pmn[k] = smn[k] = tree[i - 1][k][j ^ 1];
            for (int k = 1; k < 4096; ++k) pmn[k] = min(pmn[k], pmn[k - 1]);
            for (int k = 4094; k >= 0; --k) smn[k] = min(smn[k], smn[k + 1]);
        }
        int val = 0;
        for (int k = i; k < N; ++k) {
            val ^= A[k];
            if (i == 0) {
                tree[k][val][j] = k - i;
                tree[k][val][j] = k - i;
            } else {
                if (j == 0) {
                    if (val > 0) tree[k][val][j] = min(tree[k][val][j], pmn[val - 1] + k - i);
                } else {
                    if (val < 4095) tree[k][val][j] = min(tree[k][val][j], smn[val + 1] + k - i);
                }
            }
            
        }
    }
    int ans = N + 1;
    for (int i = 0; i <= 4095; ++i) for (int j = 0; j < 2; ++j) ans = min(ans, tree[N - 1][i][j]);
    cout << ans;
}