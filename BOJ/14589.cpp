#include <bits/stdc++.h>
using namespace std;

int N, Q;
pair<int, int> line[150001];
int f[150001][18];

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> line[i].first >> line[i].second;
	
	vector<int> v;
	for (int i = 1; i <= N; ++i) v.push_back(i);
	sort(v.begin(), v.end(), [](int a, int b) {
		if (line[a].second == line[b].second) return line[a].first > line[b].first;
		return line[a].second < line[b].second;
	});
	vector<int> arr;
	for (auto i: v) {
		while (!arr.empty() && line[arr.back()].first >= line[i].first) arr.pop_back();
		arr.push_back(i);
	}

	int idx = 0;
	for (auto i: v) {
		while (idx + 1 < arr.size() && line[arr[idx + 1]].first <= line[i].second) ++idx;
		if (line[arr[idx]].second <= line[i].second) {
			f[i][0] = -1;
			continue;
		}
		f[i][0] = arr[idx];
	}
	for (int i = 1; i < 18; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (f[j][i - 1] != -1) f[j][i] = f[f[j][i - 1]][i - 1];
			else f[j][i] = -1;
		}
	}
	// for (int i =1 ; i <= N; ++i) cout << f[i][0] << ' ';
	// cout << '\n';
	cin >> Q;
	while (Q--) {
		int A, B; cin >> A >> B;
		if (line[A].second > line[B].second) swap(A, B);
		if (line[A].second >= line[B].first) {
			cout << 1 << '\n';
			continue;
		}
		int ans = 0;
		for (int i = 17; i >= 0; --i) {
			int tmp = f[A][i];
			if (tmp == -1) continue;
			if (line[tmp].second < line[B].first) {
				ans += (1 << i);
				A = tmp;
			}
		}
		int tmp = f[A][0];
		if (tmp == -1) {
			cout << -1 << '\n';
			continue;
		}
		cout << ans + 2 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}