#include <bits/stdc++.h>
using namespace std;

int H, N;
vector<pair<int, int>> v;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> H >> N;
    v.resize(N);
    for (int i = 0; i < N; ++i) {
        int r, c; cin >> r >> c;
        v.push_back(make_pair(c, i));
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<int> ans(N);
    for (int i = 0; i < N; ++i) ans[v[i].second] = N - i;
    cout << "YES\n";
    for (auto i: ans) cout << i << ' ';
}