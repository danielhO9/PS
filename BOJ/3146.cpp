#include <bits/stdc++.h>
using namespace std;

int N, K;
int arr[1001][1001];
int sm[1001][1001][10];
int cnt[10];
int l[10], r[10];

pair<int, int> f(int i, int j, int len, int k) {
    pair<int, int> ret = make_pair(0, 0);
    if (len == 0) return ret;
    assert(i + len - 1 <= N && j + len - 1 <= N);
    ret.first += sm[i + len - 1][j + len - 1][k];
    ret.first -= sm[i - 1][j + len - 1][k];
    ret.first -= sm[i + len - 1][j - 1][k];
    ret.first += sm[i - 1][j - 1][k];
    if (k == K) return ret;
    
    ret.second += sm[i + len - 1][j + len - 1][k + 1];
    ret.second -= sm[i - 1][j + len - 1][k + 1];
    ret.second -= sm[i + len - 1][j - 1][k + 1];
    ret.second += sm[i - 1][j - 1][k + 1];
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        string s; cin >> s;
        for (int j = 0; j < N; ++j) if ('1' <= s[j] && s[j] <= '9') arr[i][j + 1] = s[j] - '0';
    }
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) ++cnt[arr[i][j]];
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) for (int k = 1; k <= K; ++k) sm[i][j][k] = sm[i][j - 1][k] + (arr[i][j] == k);
        for (int j = 1; j <= N; ++j) for (int k = 1; k <= K; ++k) sm[i][j][k] += sm[i - 1][j][k];
    }
    for (int i = 1; i <= K; ++i) l[i] = N;
    for (int k = K; k >= 1; --k) {
        // for (int i = 1; i <= N; ++i) {
        //     for (int j =1 ; j <= N; ++j) cout << sm[i][j][k] << ' ';
        //     cout << '\n';
        // }
        // cout << '\n';
        for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) {
            int s = 0, e = min(N - i, N - j) + 1, m;
            auto val = f(i, j, e, k);
            if (val.first == cnt[k]) {
                while (s + 1 < e) {
                    m = (s + e) / 2;
                    val = f(i, j, m, k);
                    if (val.first == cnt[k]) e = m;
                    else s = m;
                }
                val = f(i, j, e, k);
                if (val.second + val.first != e * e) continue;
                
                l[k] = min(l[k], e);

                s = e; e = min(N - i, N - j) + 2;
                while (s + 1 < e) {
                    m = (s + e) / 2;
                    val = f(i, j, m, k);
                    if (val.second + val.first == m * m) s = m;
                    else e = m;
                }
                r[k] = max(r[k], s);
            }
        }
        if (k != K) {
            for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) sm[i][j][k] += sm[i][j][k + 1];
        }
    }
    for (int i = 1; i <= K; ++i) cout << l[i] << ' ' << r[i] << '\n';
    
}