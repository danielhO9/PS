#include <bits/stdc++.h>
using namespace std;

int M, N;
vector<int> arr[100];
vector<int> same[100];

void solve() {
	cin >> M >> N;
	for (int i = 0; i < M; ++i) {
		vector<pair<int, int>> v;
		for (int j = 0; j < N; ++j) {
			int tmp; cin >> tmp;
			v.push_back({tmp, j});
		}
		sort(v.begin(), v.end());
		for (int j = 0; j < N; ++j) {
			arr[i].push_back(v[j].second);
			if (j != 0 && v[j].first == v[j - 1].first) same[i].push_back(1);
			else same[i].push_back(0);
			same[i].push_back(0);
		}
	}
	int ans = 0;
	for (int i = 0; i < M; ++i) for (int j = i + 1; j < M; ++j) {
		bool flag = true;
		for (int k = 0; k < N; ++k) if (same[i][k] != same[j][k]) flag = false;
		for (int k = 0; k < N; ++k) if (arr[i][k] != arr[j][k]) flag = false;
		if (flag) ++ans;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}