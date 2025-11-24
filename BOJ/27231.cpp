#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> digit;
set<ll> st;

void solve() {
    ll n; cin >> n;
    digit.clear();
    st.clear();

    while (n) {
        digit.push_back(n % 10);
        n /= 10;
    }
    reverse(digit.begin(), digit.end());

    int sz = digit.size();

    for (int i = 0; i < (1 << (sz - 1)); ++i) {
        ll val = 0, cur = 0;
        for (int j = 0; j < sz; ++j) {
            cur = cur * 10 + digit[j];
            if ((i >> j & 1) || j == sz - 1) {
                val += cur;
                cur = 0;
            }
        }
        st.insert(val);
    }
    bool flag = true;
    for (ll i: digit) if (i >= 2) flag = false;
    if (flag) {
        ll tmp = 0;
        for (ll i: digit) tmp += i;
        if (st.find(tmp) != st.end()) cout << "Hello, BOJ 2023!\n";
        else cout << 0 << '\n';
        return;
    }
    ll mx = *st.rbegin();
    ll m = 1;
    ll ans = 0;
    while (true) {
        ll tmp = 0;
        for (auto i: digit) tmp += pow(i, m);
        if (st.find(tmp) != st.end()) ++ans;
        if (tmp > mx) break;
        ++m;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}