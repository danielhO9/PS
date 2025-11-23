#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> adj[1001];
int val[1001][1001];

void solve() {
    cin >> N;
    deque<int> dq;
    for (int i = 1; i <= N; ++i) dq.push_back(i);
    for (int i = 1; i <= N; ++i) adj[i].clear();
    for (int i = 0; i < N - 1; ++i) {
        // until N - i
        cout << "? ";
        for (int j: dq) cout << j << ' ';
        cout << '\n';
        cout.flush();

        for (int j = 0; j < N; ++j) {
            int tmp; cin >> tmp;
            int idx = dq[j];
            if (idx <= N - i) val[idx][N - i] = tmp;
        }

        dq.push_front(dq.back());
        dq.pop_back();
    }

    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            int dif = val[i][j] - val[i][j - 1];
            for (int k = 0; k < dif; ++k)
                adj[i].push_back(j);
        }
    }

    int sm = 0;
    for (int i = 1; i <= N; ++i) sm += adj[i].size();
    cout << "! " << sm << '\n';
    for (int i = 1; i <= N; ++i) {
        for (int j: adj[i]) cout << i << ' ' << j << '\n';
    }
    cout.flush();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}