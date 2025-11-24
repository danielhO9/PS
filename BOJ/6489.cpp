#include <bits/stdc++.h>
using namespace std;

map<string, vector<tuple<string, int, int>>> adj;

void solve() {
    adj.clear();
    string s;
    while (true) {
        cin >> s;
        if (s == "0000") break;

        string src = s;

        cin >> s;
        int l = stoi(s);

        cin >> s;
        int d = stoi(s);

        cin >> s;
        string e = s;
        adj[src].push_back({e, l, d});
    }

    while (true) {
        cin >> s;
        if (s == "9000") break;

        int t = stoi(s);
        string ss = s;

        cin >> s;
        string prv = s;
        string cur = s;
        set<string> vis;
        
        while (true) {
            if (vis.find(cur) != vis.end()) {
                cur = "9999";
                break;
            }
            vis.insert(cur);
            bool flag = false;
            for (auto [i, j, k]: adj[cur]) {
                if (j <= t && t <= j + k) {
                    flag = true;
                    cur = i;
                }
            }
            if (!flag) break;
        }
        cout << "AT " << ss << " CALL TO " << prv << " RINGS " << cur << '\n';
    }

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) {
        cout << "SYSTEM " << i + 1 << '\n'; 
        solve();
    }
}