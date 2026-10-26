#include <bits/stdc++.h>
using namespace std;

vector<int> ans(2001);

int query(int i) {
    cout << "? " << i << endl;
    char c; cin >> c;
    if (c == '>') return 1;
    if (c == '<') return -1;
    return 0;
}

void dnq(vector<int>& V, int l, int r) {
    if (l == r) {
        ans[V[0]] = l;
        return;
    }
    random_device rd;
    shuffle(V.begin(), V.end(), rd);
    while (true) {
        if (query(V[0]) == 0) break;
    }
    int n = V.size();
    vector<int> u, d;
    int ucnt = 0, dcnt = 0;
    for (int i = 1; i < n; ++i) {
        if (query(V[i]) == 1) {
            u.push_back(V[i]);
            ++ucnt;
        } else {
            d.push_back(V[i]);
            ++dcnt;
        }
        query(V[0]);
    }
    ans[V[0]] = l + dcnt;
    if (ucnt) dnq(u, l + dcnt + 1, r);
    if (dcnt) dnq(d, l, l + dcnt -1);
}

void solve() {
    int n; cin >> n;
    vector<int> V;
    for (int i = 1; i <= n; ++i) V.push_back(i);
    dnq(V, 1, n);
    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}