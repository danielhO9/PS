#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> adj[100001];
int rt;
vector<pair<int, int>> q[100001];
int ans[100001];

deque<int> dfs(int v) {
    deque<int> tot;
    for (auto u: adj[v]) {
        deque<int> par = dfs(u);
        par.push_front(0);
        if (par.size() > tot.size()) swap(par, tot);
        for (int i = 0; i < par.size(); ++i) tot[i] += par[i];
    }
    if (tot.size() == 0) tot.push_back(0);
    ++tot[0];
    for (auto i: q[v]) {
        if (tot.size() > i.first) ans[i.second] = tot[i.first];
    }
    return tot;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int p; cin >> p;
        if (p == -1) rt = i;
        else adj[p].push_back(i);
    }
    int m; cin >> m;
    for (int i = 0; i < m; ++i) {
        int v, k; cin >> v >> k;
        q[v].push_back({k, i});
    }
    dfs(rt);
    for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}