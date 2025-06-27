#include <bits/stdc++.h>
using namespace std;

int N, M, Q;
int a[200001], l[200000], r[200000];
bool inc[200001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> Q;
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 0; i < M; ++i) cin >> l[i];
    for (int i = 0; i < M; ++i) cin >> r[i];
    sort(l, l + M); sort(r, r + M);
    multiset<int> s;
    vector<pair<int, int>> v;
    for (int i = 0; i < M; ++i) v.push_back(make_pair(l[i], r[i]));
    sort(v.begin(), v.end());
    int cur = 0;
    for (auto i: v) {
        if (cur < i.second) {
            for (int j = max(i.first, cur + 1); j <= i.second; ++j) inc[j] = true;
            cur = i.second;
        }
    }
    // for (int i = 1; i <= N; ++i) cout << inc[i] << ' ';
    // cout << '\n';
    for (int i = 1; i <= N; ++i) if (inc[i]) s.insert(a[i]);
    bool flag = false;
    for (int i = 0; i < M; ++i) if (l[i] > r[i]) flag = true;
    while (Q--) {
        int i, j; cin >> i >> j;
        if (flag) {
            cout << (int) 1e9 << '\n';
            continue;
        }
        if (i != j) {
            if (inc[i]) s.erase(s.find(a[i]));
            if (inc[j]) s.erase(s.find(a[j]));
            swap(a[i], a[j]);
            if (inc[i]) s.insert(a[i]);
            if (inc[j]) s.insert(a[j]);
        }
        if (s.empty()) cout << 1000000000 << '\n';   
        else cout << *(s.rbegin()) << '\n';
    }
}