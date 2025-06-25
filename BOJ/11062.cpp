#include <bits/stdc++.h>
using namespace std;

int N;
int arr[1000];
pair<int, int> cache[1000][1000];

void matchCache(int l, int r) {
    auto& ret = cache[l][r];
    if (ret.first != -1) return;
    if (l == r) {
        ret = make_pair(0, arr[l]);
        return;
    }
    if (l + 1 == r) {
        ret = make_pair(arr[l] < arr[r], max(arr[l], arr[r]));
        return;
    }
    matchCache(l + 1, r); matchCache(l + 2, r); matchCache(l + 1, r - 1); matchCache(l, r - 1); matchCache(l, r - 2);
    
    ret = make_pair(0, arr[l] + (cache[l + 1][r].first == 0 ? cache[l + 2][r].second : cache[l + 1][r - 1].second));
    int val = arr[r] + (cache[l][r - 1].first == 0 ? cache[l + 1][r - 1].second : cache[l][r - 2].second);
    if (val > ret.second) ret = make_pair(1, val);
    return;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cache[i][j].first = -1;
    matchCache(0, N - 1);
    cout << cache[0][N - 1].second << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}