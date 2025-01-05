#include<bits/stdc++.h>
using namespace std;

int n, m;
int h[50][50];
int cache[50][50001];
int cnt[1001];

int getMx() {
	memset(cache, 0XC0, sizeof(cache));
	vector<int> v;
	int sum = 0;
	
	for (int i = 0; i < n; ++i) {
		memset(cnt, 0, sizeof(cnt));
		int nxt = (i == n - 1 ? 0 : i + 1);
		for (int j = 0; j < m; ++j) ++cnt[h[i][j] - h[nxt][j] + 500];
		int mx = *max_element(cnt, cnt + 1001);
		v.push_back(mx); sum += mx;
		if (i == 0) {
			for (int j = 0; j <= 1000; ++j) cache[i][j] = max(cache[i][j], cnt[j]);
		} else {
			for (int j = 0; j <= 1000 * i; ++j) cache[i][j] = cache[i - 1][j];
			for (int j = 0; j <= 1000; ++j) if (cnt[j]) {
				for (int k = 0; k <= 1000 * i; ++k) {
					cache[i][j + k] = max(cache[i][j + k], cache[i - 1][k] + cnt[j]);
				}
			}
		}

	}
	int ret = cache[n - 1][500 * n];
	ret = max(ret, sum - *min_element(v.begin(), v.end()));
	return ret;
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> h[i][j];
	int ans = getMx();
	swap(n, m);
	for (int i = 0; i < 50; ++i) for (int j = i + 1; j < 50; ++j) swap(h[i][j], h[j][i]);
	ans += getMx();
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}