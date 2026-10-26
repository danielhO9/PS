#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
string S[99];
int score[99];

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> S[i];
    for (int j = 0; j < M; ++j) {
        int cnt[2] = {0, 0};
        for (int i = 0; i < N; ++i) ++cnt[S[i][j] - '0'];
        if (cnt[0] == 0 || cnt[1] == 0) {
            for (int i = 0; i < N; ++i) ++score[i];
        } else if (cnt[0] < cnt[1]) {
            for (int i = 0; i < N; ++i) if (S[i][j] == '0') ++score[i];
        } else {
            for (int i = 0; i < N; ++i) if (S[i][j] == '1') ++score[i];
        }
    }
    int mx = 0;
    for (int i = 0; i < N; ++i) mx = max(mx, score[i]);
    for (int i = 0; i < N; ++i) if (score[i] == mx) cout << i + 1 << ' ';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}