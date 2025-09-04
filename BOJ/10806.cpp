#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[100001];
const int MAX_V = 100001;

int ord[MAX_V], low[MAX_V];
bool vis[MAX_V];
int cnt = 0, col = 0;
vector<int> bcc[MAX_V];
vector<vector<int>> vs;

void dfs(int v, int p) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    for (auto u: adj[v]) if (u != p) {
        if (ord[u]) low[v] = min(low[v], ord[u]);
        else {
            dfs(u, v);
			low[v] = min(low[u], low[v]);
        }
    }
}

void color(int v, int c, int p) {
    if (c > 0) bcc[v].push_back(c);
    vis[v] = true;
    for (auto u: adj[v]) if (u != p) {
        if (vis[u]) continue;
        if (low[u] >= ord[v]) {
            bcc[v].push_back(++col);
            color(u, col, v);
        } else color(u, c, v);
    }
}

// 0-index
struct UF {
	vector<int> par, rk;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_rank(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};

// V: maximum vertex + 1
// 1-index
void getBcc(int V) {
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(i, 0);
    for (int i = 1; i < V; ++i) if (!vis[i]) color(i, 0, 0);
}

int par[MAX_V];
set<int> nadj[MAX_V];

void dfs2(int v, int p, vector<int>& leaves) {
    int cnt = 0;
    for (int u: nadj[v]) if (u != p) {
        dfs2(u, v, leaves);
        ++cnt;
    }
    if (cnt == 0) {
        leaves.push_back(v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    getBcc(N + 1);
    vs.resize(col + 1);
    for (int i = 1; i <= N; ++i) {
        for (int j: bcc[i]) vs[j].push_back(i);
    }
    UF uf {N + 1};
    for (int i = 1; i <= col; ++i) {
        bool flag = false;
        if (vs[i].size() > 2) flag = true;
        else if (vs[i].size() == 2) {
            int a = vs[i][0], b = vs[i][1];
            if (adj[a].size() > adj[b].size()) swap(a, b);
            int cnt = 0;
            for (int v: adj[a]) if (v == b) ++cnt;
            if (cnt > 1) flag = true; 
        }
        if (flag) {
            for (int j = 1; j < vs[i].size(); ++j) uf.union_rank(vs[i][j], vs[i][j - 1]);
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j: adj[i]) {
            int ii = uf.find(i);
            int jj = uf.find(j);
            if (ii == jj) continue;
            nadj[ii].insert(jj);
            nadj[jj].insert(ii);
        }
    }
    vector<int> tmp;
    for (int i = 1; i <= N; ++i) if (i == uf.find(i)) tmp.push_back(i);
    if (tmp.size() == 1) {
        cout << 0;
        return 0;
    }
    if (tmp.size() == 2) {
        cout << 1 << '\n' << tmp[0] << ' ' << tmp[1];
        return 0;
    }
    int rt = -1;
    for (auto i: tmp) if (nadj[i].size() >= 2) {
        rt = i;
        break;
    }
    assert(rt != -1);
    vector<int> leaves;
    dfs2(rt, 0, leaves);
    int n = leaves.size();
    int m = (n + 1) / 2;
    cout << m << '\n';
    for (int i = 0; i < n / 2; ++i) {
        cout << leaves[i] << ' ' << leaves[i + m] << '\n';
    }
    if (n % 2) {
        cout << rt << ' ' << leaves[n / 2];
    }
}