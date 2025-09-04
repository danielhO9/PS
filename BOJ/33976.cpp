#include <bits/stdc++.h>
using namespace std;

int N, M, K;
vector<int> adj[1001];
int F[501][501];
vector<vector<int>> team[2];

const int MAX_V = 1001;
int ord[MAX_V], low[MAX_V];
bool inS[MAX_V];
int cnt = 0;

void dfs(vector<vector<int>>& ret, stack<int>& s, int v) {
    ord[v] = ++cnt;
    low[v] = ord[v];
    s.push(v);
    inS[v] = true;
    for (auto u: adj[v]) {
        if (inS[u]) low[v] = min(low[v], ord[u]);
        else if (!ord[u]) {
            dfs(ret, s, u);
			low[v] = min(low[u], low[v]);
        }
    }
    if (low[v] == ord[v]) {
        vector<int> scc;
        while (true) {
            int cur = s.top(); s.pop();
            inS[cur] = false;
            scc.push_back(cur);
            if (cur == v) break;
        }
        ret.push_back(scc);
    }
}

// V: maximum vertex + 1
// 1-index
vector<vector<int>> getScc(int V) {
    memset(ord, 0, sizeof(ord));
    memset(low, 0, sizeof(low));
    memset(inS, 0, sizeof(inS));
    cnt = 0;
	vector<vector<int>> ret;
    stack<int> s;
	for (int i = 1; i < V; ++i) if (!ord[i]) dfs(ret, s, i);
	return ret;
}

void addEdge(int u, int v) {
    int ou, ov;
    if (u > N) ou = u - N;
    else ou = u + N;
    if (v > N) ov = v - N;
    else ov = v + N;
    adj[ou].push_back(v);
    adj[ov].push_back(u);
}

bool available(int x) {
    for (int i = 1; i <= 2 * N; ++i) adj[i].clear();
    for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) if (F[i][j] < x) {
        addEdge(i, j);
        addEdge(i + N, j + N);
    }
    for (int i = 0; i < 2; ++i) {
        for (const auto& v: team[i]) {
            for (int j = 0; j < v.size(); ++j) for (int k = j + 1; k < v.size(); ++k) {
                if (i == 0) addEdge(v[j], v[k]);
                else addEdge(v[j] + N, v[k] + N);
            }
        }
    }
    auto scc = getScc(2 * N + 1);
    vector<int> num(2 * N + 1);
    for (int i = 0; i < scc.size(); ++i) {
        for (int j: scc[i]) num[j] = i;
    }
    for (int i = 1; i <= N; ++i) if (num[i] == num[i + N]) {
        return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        int B; cin >> B;
        team[0].push_back({});
        for (int j = 0; j < B; ++j) {
            int x; cin >> x;
            team[0].back().push_back(x);
        }
    }
    for (int i = 0; i < K; ++i) {
        int B; cin >> B;
        team[1].push_back({});
        for (int j = 0; j < B; ++j) {
            int x; cin >> x;
            team[1].back().push_back(x);
        }
    }
    for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) cin >> F[i][j];
    if (N == 2) {
        cout << "INFINITY";
        return 0;
    }
    int l = 0, r = 1e9; ++r;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (available(mid)) l = mid;
        else r = mid;
    }
    cout << l;
}