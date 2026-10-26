#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int deg[501];
vector<int> vertices[501];

int query(int x, const vector<int>& s, int l, int r) {
    cout << "? " << x << ' ';
    cout << r - l + 1 << ' ' << x << ' ';
    for (int i = l; i < r; ++i) cout << s[i] << ' ';
    cout << '\n';
    cout.flush();
    int ret; cin >> ret;
    return ret;
}

int find(int x, const vector<int>& s, int l, int r) {
    if (l + 1 == r) return s[l];
    int mid = (l + r) / 2;
    int ll = query(x, s, l, mid);
    if (ll >= 2) return find(x, s, l, mid);
    return find(x, s, mid, r);
}

void solve() {
    cin >> n;
    vector<int> v;
    for (int i = 1; i <= n; ++i) v.push_back(i);
    int mx = 0;
    for (int i = 1; i <= n; ++i) {
        cout << "? " << i << ' ';
        cout << n << ' ';
        for (int i = 1; i <= n; ++i) cout << i << ' ';
        cout << '\n';
        cout.flush();
        cin >> deg[i];
        mx = max(mx, deg[i]);
    }
    for (int i = 1; i <= n; ++i) vertices[i].clear();
    for (int i = 1; i <= n; ++i) vertices[deg[i]].push_back(i);
    vector<int> ans;
    ans.push_back(vertices[mx][0]);
    for (int i = mx - 1; i >= 1; --i) {
        int x = ans.back();
        int y = find(x, vertices[i], 0, vertices[i].size());
        ans.push_back(y);
    }
    cout << "! " << ans.size() << ' ';
    for (auto i: ans) cout << i << ' ';
    cout << '\n';
    cout.flush();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}