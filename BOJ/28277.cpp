#include <bits/stdc++.h>
using namespace std;

int N, Q;
set<int> s[500001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        int sz; cin >> sz;
        for (int j = 0; j < sz; ++j) {
            int val; cin >> val; s[i].insert(val);
        }
    }
    while (Q--) {
        int t, a, b;
        cin >> t >> a;
        if (t == 1) {
            cin >> b;
            if (s[a].size() < s[b].size()) swap(s[a], s[b]);
            for (int i: s[b]) s[a].insert(i);
            s[b].clear();
        } else {
            cout << s[a].size() << '\n';
        }
    }
}