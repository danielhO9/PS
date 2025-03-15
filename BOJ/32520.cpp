#include <bits/stdc++.h>
using namespace std;

int dis[1001][1001][4];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    pair<int, int> a, b;
    memset(dis, -1, sizeof(dis));
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    queue<vector<int>> q;
    q.push({a.first, a.second, 0}); dis[a.first + 500][a.second + 500][0] = 0;
    while (!q.empty()) {
        auto here = q.front(); q.pop();
        int val = dis[here[0] + 500][here[1] + 500][here[2]];
        assert(here.size() == 3);
        int nxt = (here[2] + 1) % 4;
        if (here[0] + 1 <= 500 && dis[here[0] + 1 + 500][here[1] + 500][nxt] == -1) {
            dis[here[0] + 1 + 500][here[1] + 500][nxt] = val + 1;
            q.push({here[0] + 1, here[1], nxt});
        }
        if (abs(here[0] * 2) <= 500 && abs(here[1] * 2) <= 500 && dis[here[0] * 2 + 500][here[1] * 2 + 500][nxt] == -1) {
            dis[here[0] * 2 + 500][here[1] * 2 + 500][nxt] = val + 1;
            q.push({here[0] * 2, here[1] * 2, nxt});
        }
        if (dis[-here[1] + 500][here[0] + 500][nxt] == -1) {
            dis[-here[1] + 500][here[0] + 500][nxt] = val + 1;
            q.push({-here[1], here[0], nxt});
        }
    }
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int K; cin >> K; int k = K; k %= 4;
        if (dis[b.first + 500][b.second + 500][k] == -1) cout << "NO\n";
        else if (dis[b.first + 500][b.second + 500][k] <= K) cout << "YES\n";
        else cout << "NO\n";
        
    }

}