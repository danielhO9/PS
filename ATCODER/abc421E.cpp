#include <bits/stdc++.h>
using namespace std;

int A[6];
map<pair<int, multiset<int>>, double> cache;
unordered_map<int, int> um;
map<multiset<int>, int> cnt[6];

void dfs(int len, multiset<int>& s) {
    if (s.size() == len) {
        ++cnt[len][s];
        return;
    }
    for (int i = 0; i < 6; ++i) {
        s.insert(A[i]);
        dfs(len, s);
        s.erase(s.find(A[i]));
    }
}

void init() {
    multiset<int> s;
    for (int i = 1; i <= 5; ++i) dfs(i, s);
}

double score(const multiset<int>& S) {
    assert(S.size() == 5);
    double ret = 0;
    um.clear();
    for (auto i: S) ++um[i];
    for (auto [i, j]: um) ret = max(ret, (double) i * j);
    return ret;
}

double matchCache(int k, const multiset<int>& S) {
    if (cache.find(make_pair(k, S)) != cache.end()) {
        return cache[make_pair(k, S)];
    }
    double& ret = cache[make_pair(k, S)];
    int rem = 5 - S.size();
    if (rem == 0) return ret = score(S);
    for (const auto& [P, w]: cnt[rem]) {
        if (k == 1) {
            multiset<int> s;
            for (auto i: S) s.insert(i);
            for (auto i: P) s.insert(i);
            ret += score(s) * w / pow(6, rem);
        } else {
            double tmp = 0.0;
            for (int i = 0; i < (1 << rem); ++i) {
                multiset<int> s = multiset<int> {S};
                multiset<int> p = multiset<int> {P};
                for (int j = 0; j < rem; ++j) {
                    if ((i >> j) & 1) s.insert(*(p.begin()));
                    p.erase(p.begin());
                }
                tmp = max(tmp, matchCache(k - 1, s));
            }
            ret += tmp * w / pow(6, rem);
        }
    }
    return ret;
}

void solve() {
    for (int i = 0; i < 6; ++i) cin >> A[i];
    init();
    multiset<int> s;
    cout.precision(6);
    cout << fixed;
    cout << matchCache(3, s);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}