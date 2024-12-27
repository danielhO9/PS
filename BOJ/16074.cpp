#include <bits/stdc++.h>
using namespace std;

int m, n, q;
int h[500][500];
int l[100000], r[100000], s[100000], e[100000];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, 1, -1};

vector<int> adj[250000];
vector<int> num;
vector<int> query[250001];
vector<int> nquery[250001];

struct UF {
	int sz;
	vector<int> par;

	void init(int _sz) {
		sz = _sz;
		par.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		par[x] = y;
	}
};

void solve() {
	cin >> m >> n >> q;
	set<int> hs;
	hs.insert(0);
	for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
		cin >> h[i][j];
		hs.insert(h[i][j]);
	}
	for (auto i: hs) num.push_back(i);
	for (int i = 0; i < q; ++i) {
		int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
		--x1; --x2; --y1; --y2;
		s[i] = x1 * n + y1; e[i] = x2 * n + y2;
	}
	for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
		for (int k = 0; k < 4; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < m && 0 <= nj && nj < n) adj[i * n + j].push_back(ni * n + nj);
		}
	}
	for (int i = 0; i < q; ++i) {
		l[i] = 0; r[i] = (int) num.size() - 1;
		int mid = (l[i] + r[i]) / 2;
		if (l[i] + 1 < r[i]) query[mid].push_back(i);
	}

	while (true) {
		priority_queue<pair<int, int>> pq;
		for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) pq.push({-h[i][j], i * n + j});
		UF uf; uf.init(n * m);
		bool flag = false;
		// for (int i = 0; i < num.size(); ++i) cout << query[i].size() << ' ';
		// cout << '\n';
		for (int i = 0; i < num.size(); ++i) {
			while (!pq.empty() && -pq.top().first <= num[i]) {
				int v = pq.top().second; pq.pop();
				for (auto u: adj[v]) if (h[u / n][u % n] <= num[i]) uf.union_path(u, v);
			}
			for (int j: query[i]) {
				flag = true;
				if (h[s[j] / n][s[j] % n] <= num[i] && h[e[j] / n][e[j] % n] <= num[i] && uf.find(s[j]) == uf.find(e[j])) r[j] = i;
				else l[j] = i;
				int mid = (l[j] + r[j]) / 2;
				if (l[j] + 1 < r[j]) nquery[mid].push_back(j);
			}
			query[i].clear();
		}
		if (flag == false) break;
		swap(query, nquery);
	}
	for (int i = 0; i < q; ++i) cout << num[r[i]] << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}