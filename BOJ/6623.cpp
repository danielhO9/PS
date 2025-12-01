#include <bits/stdc++.h>
using namespace std;

int C, R, cnt;
map<string, int> m;
double dis[200][200];

void solve() {
    for (int m = 0; m < C; ++m) {
        for (int s = 0; s < C; ++s) for (int e = 0; e < C; ++e) {
            dis[s][e] = max(dis[s][e], dis[s][m] * dis[m][e]);
        }
    }
    for (int i = 0; i < C; ++i) if (dis[i][i] > 1.0) {
        cout << "Arbitrage\n";
        return;
    }
    cout << "Ok\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> C;
        if (C == 0) break;
        m.clear();
        for (int i = 0; i < C; ++i) for (int j = 0; j < C; ++j) dis[i][j] = 0.0;
        for (int i = 0; i < C; ++i) dis[i][i] = 1.0;
        cnt = 0;
        for (int i = 0; i < C; ++i) {
            string s; cin >> s;
            m[s] = cnt++;
        }
        cin >> R;
        for (int i = 0; i < R; ++i) {
            string s1, s2, s3; cin >> s1 >> s2 >> s3;
            int s = m[s1], e = m[s2];
            int idx = -1;
            int l = s3.size();
            for (int j = 0; j < s3.size(); ++j) if (s3[j] == ':') idx = j;
            double d = stod(s3.substr(idx + 1, l - idx - 1)) / stod(s3.substr(0, idx));
            // cout << d << '\n';
            dis[s][e] = max(dis[s][e], d);
        }

        solve();
    }
}