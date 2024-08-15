#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<int> adj[100001];
vector<int> nadj[200001];
int num[200001];
bool vis[100001];
int idx;
vector<tuple<int, int, int>> ans;
map<pair<int, int>, bool> m;

void dfs(int v, int p) {
    for (int u: adj[v]) if (m[{u, v}] == 0) {
        m[{u, v}] = 1;
        m[{v, u}] = 1;
        if (vis[u]) {
			// cout << idx << ' ' << v << '\n';
            num[idx] = u;
            nadj[idx].push_back(v);
            nadj[v].push_back(idx);
            ++idx;
        } else {
			// cout << u << ' ' << v << '\n';
			nadj[u].push_back(v);
			nadj[v].push_back(u);
			vis[u] = true;
			dfs(u, v);
		}
    }
}

int getAns(int v, int p) {
    vector<int> c;
    for (auto u: nadj[v]) if (u != p) {
        int tmp = getAns(u, v);
        if (tmp != 0) {
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
	idx = N + 1;
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= N; ++i) num[i] = i;
    for (int i = 1; i <= N; ++i) if (!vis[i]) {
        vis[i] = true; dfs(i, 0);
        getAns(i, 0);
    }
    cout << ans.size() << '\n';
    for (auto i: ans) {
        cout << num[get<0>(i)] << ' ' << num[get<1>(i)] << ' ' << num[get<2>(i)] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}