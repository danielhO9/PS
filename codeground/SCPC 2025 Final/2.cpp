#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll MOD[2] = {998244353, 1000000009};

int N;
string A[1000];
ll pf[1024][2];
unordered_map<ll, int> m;
vector<pair<int, int>> v;
int cnt;

void init() {
    pf[0][0] = pf[0][1] = 5;
    for (int j = 0; j < 2; ++j) {
        for (int i = 1; i < 1024; ++i) pf[i][j] = (pf[i - 1][j] * 5) % MOD[j];
    }
}

ll hashing(const string& s, int l, int r) {
    ll t = 1;
    for (int j = 0; j < 2; ++j) {
        ll ret = 0;
        for (int i = l; i < r; ++i) {
            ret += (s[i] - '0') * pf[i][j];
            ret %= MOD[j];
        }
        t *= ret;
    }
    return t;
}

int add(string& s, int l, int r) {
    ll h = hashing(s, l, r);
    if (m.find(h) != m.end()) return m[h];

    int mid = (l + r) >> 1;
    
    int lll = add(s, l, mid);
    int rrr = add(s, mid, r);

    if (lll == 0 || rrr == 0) return lll + rrr;
    v.push_back(make_pair(lll, rrr));
    return m[h] = ++cnt;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        A[i] = s;
    }

    int nn = N;
    while (__builtin_popcount(nn) != 1) {
        ++nn;
    }

    for (int i = 0; i < N; ++i) {
        while (A[i].size() < nn) A[i].push_back('0');
    }

    m.clear();
    v.clear();

    m[0] = 0;
    string tmp;
    for (int i = 0; i < nn; ++i) tmp += '0';
    for (int i = 0; i < N; ++i) {
        tmp[i] = '1';
        m[hashing(tmp, 0, nn)] = i + 1;
        tmp[i] = '0';
    }
    cnt = N;
    for (int i = 0; i < N; ++i) add(A[i], 0, nn - 1);

    cout << v.size() << '\n';
    for (auto [i, j]: v) {
        cout << i << ' ' << j << '\n';
    }
    for (int i = 0; i < N; ++i) cout << m[hashing(A[i], 0, nn)] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}