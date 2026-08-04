#include <bits/stdc++.h>
using namespace std;

int N;
string S;

string mn(const string& a, const string& b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] < b[i]) return a;
        if (a[i] > b[i]) return b;
    }
    return a;
}

void solve() {
    cin >> N >> S;
    string ans = S;
    for (int i = 0; i < N; ++i) {
        string tmp; tmp += S[N - 1];
        for (int j = 0; j < N - 1; ++j) tmp += S[j];
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < tmp.size(); ++k) {
                ++tmp[k];
                if (tmp[k] > '9') tmp[k] = '0';
            }
            ans = min(ans, tmp);
        }
        S = tmp;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}