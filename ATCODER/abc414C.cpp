#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A, N;

void solve() {
    cin >> A >> N;
    vector<ll> v;
    int sz = 1;
    for (ll cur = 10; cur <= 1000000; cur *= 10) {
        for (ll i = 1; i < cur; ++i) {
            string s = to_string(i);
            reverse(s.begin(), s.end());
            while (s.size() < sz) s.push_back('0');
            reverse(s.begin(), s.end());
            string ss = s;
            reverse(ss.begin(), ss.end());
            string sss = ss + s;
            sss = to_string(stol(sss));
            int sz = sss.size();
            bool flag = true;
            for (int i = 0; i < sz; ++i) if (sss[i] != sss[sz - 1 - i]) {
                flag = false;
                break;
            }
            if (flag && stol(ss + s) <= N) v.push_back(stol(sss));
            ss.pop_back();
            sss = ss + s;
            sss = to_string(stol(sss));
            sz = sss.size();
            flag = true;
            for (int i = 0; i < sz; ++i) if (sss[i] != sss[sz - 1 - i]) {
                flag = false;
                break;
            }
            if (flag && stol(ss + s) <= N) v.push_back(stol(sss));
        }
        ++sz;
    }
    ll ans = 0;
    for (auto i: v) {
        string s;
        ll val = i;
        while (val) {
            s += (char) ((val % A) + '0');
            val /= A;
        }
        int sz = s.size();
        bool flag = true;
        for (int i = 0; i < sz; ++i) if (s[i] != s[sz - 1 - i]) flag = false;
        if (flag) {
            ans += i;
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}
