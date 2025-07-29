#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, MOD - 1);

ll val[1 << 16];
vector<ll> v;
int n;
vector<int> ans;
vector<int> tar;

void getV(int sz) {
    while (true) {
        set<ll> s;
        vector<ll> a;
        for (int i = 0; i < sz; ++i) a.push_back(dist(gen));
        for (int i = 0; i < (1 << sz); ++i) {
            ll cur = 0;
            for (int j = 0; j < sz; ++j) {
                if ((i >> j) & 1) cur *= a[j];
                else cur += a[j];
                cur %= MOD;
            }
            val[i] = cur;
            s.insert(cur);
        }
        if (s.size() == (1 << sz)) {
            v = a;
            break;
        }
    }
}

void solve(int l, int r) {
    int sz = r - l + 1;
    if (sz != 16) getV(sz);
    vector<ll> query;
    for (int i = 0; i < l + 1; ++i) query.push_back(0);
    for (auto i: v) query.push_back(i);
    for (int i = r + 1; i < n; ++i) {
        if (ans[i]) query.push_back(1);
        else query.push_back(0);
    }
    cout << "? ";
    for (auto i: query) cout << i << ' ';
    cout << '\n';
    cout.flush();
    ll tmp; cin >> tmp;

    for (int i = 0; i < (1 << sz); ++i) if (val[i] == tmp) {
        for (int j = 0; j < sz; ++j) {
            if ((i >> j) & 1) ans[l + j] = 1;
            else ans[l + j] = 0;
        }
        return;
    }
    
    assert(false);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    ans = vector<int>(n, -1);
    getV(16);
    for (int i = n - 1; i >= 0; i -= 16) {
        solve(max(i - 15, 0), i);
    }
    cout << "! ";
    for (auto i: ans) {
        if (i) cout << 'x';
        else cout << '+';
    }
    cout << '\n';
    cout.flush();
}