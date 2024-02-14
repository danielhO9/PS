#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N;
int x = -1;
vector<int> dep(262144), w(262144);

void dfs(int v, int d, vector<LL>& W) {
	if (2 * v <= N) dfs(2 * v, d + 1, W);
	dep[++x] = d; w[x] = W[v];
	if (2 * v + 1 <= N) dfs(2 * v + 1, d + 1, W);
}

LL getMax(int l, int r) {
	vector<LL> W;
	for (int i = 0; i < N; ++i) if (l <= dep[i] && dep[i] <= r) W.push_back(w[i]);
	LL minW = 0, ans = LLONG_MIN, sum = 0;
	for (int i = 0; i < W.size(); ++i) {
		sum += W[i];
		if (i != 0) ans = max(ans, sum - minW);
		else ans = max(ans, sum);
		minW = min(minW, sum);
	}
	return ans;
}

void solve() {
	cin >> N;
	vector<LL> W(N + 1); for (int i = 1; i <= N; ++i) cin >> W[i];
	if (N == 1) { cout << W[1]; return; }
	dfs(1, 0, W);
	LL ans = LLONG_MIN;
	for (int l = 0; l < 18; ++l) for (int r = l; r < 18; ++r) ans = max(ans, getMax(l, r));
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}