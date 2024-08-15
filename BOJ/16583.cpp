#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[100001];
vector<int> nadj[200001];
int num[200001];
bool vis[100001];
int idx = N + 1;
vector<tuple<int, int, int>> ans;

void dfs(int v, int p) {
    for (int u: adj[v]) if (u != p) {
        cout << u << ' ' << v << '\n';
        if (vis[u]) {
            num[idx] = u;
            nadj[idx].push_back(v);
            nadj[idx].push_back(idx);
            ++idx;
            continue;
        }
        nadj[u].push_back(v);
        nadj[v].push_back(u);
        vis[u] = true;
        dfs(u, v);
    }
}

int getAns(int v, int p) {
    vector<int> c;
    for (auto u: nadj[v]) if (u != p) {
        int tmp = getAns(u, v);
        if (tmp) {
            ans.push_back(make_tuple(tmp, u, v));
        } else {
            c.push_back(u);
        }
    }
    for (int i = 0; i + 1 < c.size(); i += 2) {
        ans.push_back(make_tuple(c[i], v, c[i + 1]));
    }
    if (c.size() % 2) return c.back();
    else return 0;
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vis[1] = true; dfs(1, 0);
    getAns(1, 0);
    for (auto i: ans) {
        cout << get<0>(i) << ' ' << get<1>(i) << ' ' << get<2>(i) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}