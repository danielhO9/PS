#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int MAX_M, MAX_N;

vector<ll> dp_before, dp_cur;
vector<ll> V;

ll C(int i, int j) {
	ll ret = V[j];
	if (i != 0) ret -= V[i - 1];
	return ret * (j - i);
}

// min version
// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;

    int mid = (l + r) >> 1;
    pair<ll, int> best = {LLONG_MAX, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

vector<ll> dijkstra(int src, vector<vector<pair<int, ll>>>& adj) {
	const int MAX_V = adj.size();
	vector<ll> dist(MAX_V, LLONG_MAX);
	dist[src] = 0;
	priority_queue<pair<ll, int>> pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		ll cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			ll nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

// MAX_V: max vertex number
// time complexity: (V+E)logV
void solve() {
	int n, b, s, r; cin >> n >> b >> s >> r;
	int MAX_V = n + 1;
	vector<vector<pair<int, ll>>> adj(MAX_V);
	vector<vector<pair<int, ll>>> radj(MAX_V);
	for (int i = 0; i < r; ++i) {
		int u, v; ll l; cin >> u >> v >> l;
		adj[u].push_back({v, l});
		radj[v].push_back({u, l});
	}
	vector<ll> ans = dijkstra(b + 1, adj);
	vector<ll> rans = dijkstra(b + 1, radj);
	for (int i = 1; i <= b; ++i) V.push_back(ans[i] + rans[i]);
	sort(V.begin(), V.end());
	for (int i = 1; i < b; ++i) V[i] += V[i - 1];

	MAX_N = b; MAX_M = s;
	dp_before.assign(MAX_N,0);
    dp_cur.assign(MAX_N,0);

    for (int i = 0; i < MAX_N; i++)
        dp_before[i] = C(0, i);

    for (int i = 1; i < MAX_M; i++) {
        compute(0, MAX_N - 1, 0, MAX_N - 1);
        dp_before = dp_cur;
    }

    cout << dp_before[MAX_N - 1];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}