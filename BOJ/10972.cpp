#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	vector<int> v(N);
	for (int i = 0; i < N; ++i) cin >> v[i];
	for (int i = N - 2; i >= 0; --i) if (v[i] < v[i + 1]) {
		int nxt = N;
		for (int j = i + 1; j < N; ++j) if (v[j] > v[i]) nxt = min(nxt, v[j]);
		vector<int> tmp; tmp.push_back(v[i]);
		for (int j = i + 1; j < N; ++j) if (v[j] != nxt) tmp.push_back(v[j]);
		sort(tmp.begin(), tmp.end());
		for (int j = 0; j < i; ++j) cout << v[j] << ' ';
		cout << nxt << ' ';
		for (auto j: tmp) cout << j << ' ';
		return 0;
	}
	cout << -1;
}