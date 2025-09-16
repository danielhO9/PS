#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int A[6];
map<pair<int, multiset<int>>, double> cache;
map<multiset<int>, ll> cnt[6];
ll tmp[7];
ll sm = 0;

void dfs(int len, multiset<int>& s) {
    if (s.size() == len) {
        ++cnt[len][s];
        ++sm;
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

ll score(const multiset<int>& S) {
    assert(S.size() == 5);

    memset(tmp, 0, sizeof(tmp));
    for (auto i: S) ++tmp[i];
    ll ret = 0;
    for (int i = 1; i <= 6; ++i) ret = max(ret, tmp[i] * i);
    for (int i = 1; i <= 6; ++i) if (tmp[i] == 5) ret = max(ret, 50ll);
    return ret;
}

double matchCache(int k, const multiset<int>& S) {
    assert(S.size() == 5);
    if (cache.find(make_pair(k, S)) != cache.end()) return cache[make_pair(k, S)];
    double& ret = cache[make_pair(k, S)];

    if (k == 0) return ret = score(S);
    ret = 0.0;

    for (int i = 0; i < (1 << 5); ++i) {

        double rret = 0;
        multiset<int> s;

        multiset<int> p;
        for (auto j: S) p.insert(j);

        for (int j = 0; j < 5; ++j) {
            if ((i >> j) & 1) s.insert(*(p.begin()));
            p.erase(p.begin());
        }

        // s: erased

        int rem = 5 - s.size();
        if (rem == 0) rret = score(s);

        for (const auto& [P, w]: cnt[rem]) {
            multiset<int> nxt = multiset<int> {s};
            for (auto i: P) nxt.insert(i);
            ll cur = matchCache(k - 1, nxt) * 2;
            rret += matchCache(k - 1, nxt) * w / pow(6, rem);
        }
        ret = max(ret, rret);
    }
    return ret;
}

void solve() {
    for (int i = 0; i < 6; ++i) A[i] = i + 1;
    init();
    multiset<int> s;
    for (int i = 0; i < 5; ++i) {
        int tmp; cin >> tmp;
        s.insert(tmp);
    }
    
    cout << (ll) (matchCache(1, s) * pow(6, 5) + 0.5);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}