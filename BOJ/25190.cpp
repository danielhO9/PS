#include <bits/stdc++.h>
using namespace std;

int N;
int p[1000], c[1000];
vector<pair<int, int>> v;
int cache[3100][1000];

int matchCache(int curp, int n) {
    int& ret = cache[curp][n];
    if (ret != -1) return ret;
    if (n == 0) {
        if (curp >= v[n].first && curp - v[n].first < v[n].second) return 1;
        else return 0;
    }
    ret = 0;
    if (curp >= v[n].first && curp - v[n].first < v[n].second) ret = max(ret, matchCache(curp - v[n].first, n - 1) + 1);
    ret = max(ret, matchCache(curp, n - 1));
    // cout << curp << ' ' << n << ' ' << ret << '\n';
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> p[i] >> c[i];
    for (int i = 0; i < N; ++i) v.push_back(make_pair(p[i], c[i]));
    sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first + a.second < b.first + b.second;
    });
    memset(cache, -1, sizeof(cache));
    // matchCache(9, 4);
    pair<int, int> ans = make_pair(0, 0);
    for (int i = 0; i < 3100; ++i) for (int j = 0; j < N; ++j) {
        ans = max(ans, make_pair(matchCache(i, j), -i));
    }
    cout << ans.first << ' ' << -ans.second;
}