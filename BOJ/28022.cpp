#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int P, Q, deg;
};

int N;
int A[200001];
vector<Edge> adj[200001];
int dis[200001];
vector<pair<int, int>> iadj[200001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        cin >> A[i];
        for (int j = 0; j < A[i]; ++j) {
            int P, Q; cin >> P >> Q;
            adj[i + 1].push_back({P, Q, 2});
            iadj[P].push_back(make_pair(i + 1, j));
            iadj[Q].push_back(make_pair(i + 1, j));
        }
    }
    for (int i = 1; i <= N; ++i) dis[i] = INT32_MAX;
    queue<int> q; dis[N] = 0; q.push(N);
    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (auto [there, idx]: iadj[here]) if (dis[there] == INT32_MAX) {
            --adj[there][idx].deg;
            if (adj[there][idx].deg == 0) {
                q.push(there);
                dis[there] = dis[here] + 1;
            }
        }
    }
    if (dis[1] == INT32_MAX) cout << -1;
    else cout << dis[1];
}