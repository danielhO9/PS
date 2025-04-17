#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll K, C;

bool bad(string& a, string& b) {
    return stol(a) > stol(b);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> K >> C;
    string s = to_string(K);
    ll n = s.size();
    ll cs = 0;
    for (int i = 1; i < n; ++i) {
        bool flag = true;
        for (int j = 0; j < i; ++j) if (s[j] != s[n - i + j]) flag = false;
        if (flag) cs = i;
    }
    ll val = (n - cs) * (K - 1) + n;
    ll ans = 0;
    // i characters same
    string ss;
    for (int i = cs + 1; i < n; ++i) {
        ss = s;
        for (int j = 0; j < n - i; ++j) {
            for (int k = j + n - i; k < n; k += n - i) ss[k] = ss[k - (n - i)];
        }
        while (bad(s, ss)) {
            int f;
            for (int j = 0; j < n; ++j) if (s[j] > ss[j]) {
                f = j;
                break;
            }
            if (f < n - i) {
                for (int j = f; j < n; j += n - i) ++ss[j];
                continue;
            }
            for (int j = n - i - 1; j >= 0; --j) if (ss[j] != '9') {
                for (int k = j; k < n; k += n - i) ++ss[k];
                break;
            }
        }
        ll nK = stol(ss);
        ll nval = (n - i) * (nK - 1) + n;
        ll dif = nK - K;
        ans = max(ans, val - nval - C * dif);
    }
    cout << ans;
}