#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX_V = 100001;
int n;
int f[100001];
ll p[100001], m[100001], s[100001];
int vis[100001];
ll ans = 0;
vector<int> adj[MAX_V];
ll mx[100001];
int mxv[100001];

int dfs(int v, vector<int>& sccNum, stack<int>& S, vector<vector<int>>& scc, vector<int>& ord, int& cnt) {
	ord[v] = ++cnt; S.push(v);
	int result = ord[v];
	for (int u: adj[v]) {
		if (ord[u] == -1) result = min(result, dfs(u, sccNum, S, scc, ord, cnt));
		else if (sccNum[u] == -1) result = min(result, ord[u]);
	}
	if (result == ord[v]) {
		vector<int> temp;
		while (true) {
			int t = S.top(); S.pop();
			temp.push_back(t);
			sccNum[t] = scc.size();
			if (t == v) break;
		}
		scc.push_back(temp);
	}
	return result;
}

void getSCC(vector<vector<int>>& scc, vector<int>& sccNum) {
	stack<int> S; vector<int> ord(n + 1, -1); int cnt = -1;
	for (int i = 1; i <= n; ++i) if (ord[i] == -1) dfs(i, sccNum, S, scc, ord, cnt);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> f[i] >> p[i] >> m[i] >> s[i];
    for (int i = 1; i <= n; ++i) if (m[f[i]] > p[i]) adj[f[i]].push_back(i);
    for (int i = 1; i <= n; ++i) {
        mx[i] = 0; mxv[i] = -1;
        for (auto j: adj[i]) mx[i] = max(mx[i], m[i] - p[j]);
        for (auto j: adj[i]) if (mx[i] == m[i] - p[j]) mxv[i] = j;
        ans += mx[i] * s[i];
    }
	vector<vector<int>> scc;
	vector<int> sccNum(n + 1, -1);
	getSCC(scc, sccNum);
    for (auto g: scc) {
        if (g.size() == 1) continue;
        for (auto v: g) vis[v] = 1;
        bool flag = true;
        ll nxt = LLONG_MAX;
        for (auto v: g) for (auto u: adj[v]) {
            if (vis[u] == 1 && mxv[v] != u) flag = false;
            if (mxv[v] != u) nxt = min(nxt, mx[v] - (m[v] - p[u]));
            else nxt = min(nxt, mx[v]);
        }
        if (flag) ans -= nxt;
        for (auto v: g) vis[v] = 0;
    }
    cout << ans;
}