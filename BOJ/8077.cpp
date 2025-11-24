#include <bits/stdc++.h>
using namespace std;

int t, a, n;
int cache[22][80];
int ti[1000], ai[1000], wi[1000];
const int MAX = 1e6;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> t >> a;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> ti[i] >> ai[i] >> wi[i];
    for (int i = 0; i <= t; ++i) for (int j = 0; j <= a; ++j) cache[i][j] = MAX;
    cache[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<tuple<int, int, int>> v;
        for (int j = 0; j <= t; ++j) for (int k = 0; k <= a; ++k) {
            v.push_back({min(t, ti[i] + j), min(a, ai[i] + k), cache[j][k] + wi[i]});
        }
        for (auto [j, k, l]: v) {
            cache[j][k] = min(cache[j][k], l);
        }
    }
    cout << cache[t][a];
}