#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[100];

void solve() {
    cin >> n;
    string s; cin >> s;
    for (int i = 0; i < n - 1; ++i) {
        char c = s[i];
        if (c == '>') a[i] = 1;
        else a[i] = 0;
    }
    vector<int> ans;
    int l = 1, r = n;
    for (int i = n - 2; i >= 0; --i) {
        if (a[i]) ans.push_back(r--);
        else ans.push_back(l++);
    }
    ans.push_back(l);
    reverse(ans.begin(), ans.end());
    for (auto i: ans) cout << i << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}