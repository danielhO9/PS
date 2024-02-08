#include <bits/stdc++.h>
using namespace std;

int cache[300][300];
int INF = 987654321;

int matchCache(int end, int m, vector<int>& a) {
	if (m == 1) return a[end];
	if (end + 1 < m) return INF;
	int& ret = cache[end][m];
	if (ret != -1) return ret;
	ret = INF;
	for (int i = end - 1; i >= m - 2; --i) {
		ret = min(ret, max(a[end] - a[i], matchCache(i, m - 1, a)));
	}
	return ret;
}

vector<int> ans;

void reconstruct(int end, int m, vector<int>& a) {
	if (m == 1) {
		ans.push_back(end + 1);
		return;
	}
	int cnt, maxAns = INF;
	for (int i = end - 1; i >= m - 2; --i) {
		if (maxAns > max(a[end] - a[i], matchCache(i, m - 1, a))) {
			cnt = i;
			maxAns = max(a[end] - a[i], matchCache(i, m - 1, a));
		}
	}
	ans.push_back(end - cnt);
	reconstruct(cnt, m - 1, a);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, M; cin >> N >> M;
	memset(cache, -1, sizeof(cache));
	vector<int> a(N);
	for (int i = 0; i < N; ++i) {
		if (i == 0) cin >> a[0];
		else {
			cin >> a[i];
			a[i] += a[i - 1];
		}
	}
	cout << matchCache(N - 1, M, a) << '\n';
	reconstruct(N - 1, M, a);
	reverse(ans.begin(), ans.end());
	for (auto i: ans) cout << i << ' ';
}