#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int M; cin >> M;
    priority_queue<int> l, r;
    int cur; cin >> cur;
    vector<int> ans;
    ans.push_back(cur);
    for (int i = 2; i <= M; ++i) {
        int a; cin >> a;
        if (cur < a) r.push(-a);
        else l.push(a);
        if (i % 2) {
            while (l.size() != r.size()) {
                if (l.size() < r.size()) {
                    l.push(cur);
                    cur = -r.top();
                    r.pop();
                } else {
                    r.push(-cur);
                    cur = l.top();
                    l.pop();
                }
            }
            ans.push_back(cur);
        }
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
        if (i % 10 == 9) cout << '\n';
    }
    if (ans.size() % 10 != 0) cout << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}