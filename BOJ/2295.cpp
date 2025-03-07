#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; vector<int> v(N);
	for (int i = 0; i < N; ++i) cin >> v[i];
	sort(v.begin(), v.end());
	set<int> s;
	int ans = -1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= i; ++j) s.insert(v[j] + v[i]);
		for (int j = N - 1; j > i; --j) {
			if (v[j] <= ans) break;
			auto itr = s.lower_bound(v[j] - v[i]);
			if (itr != s.end() && *itr == v[j] - v[i]) {
				ans = v[j];
				break;
			}
		}
	}
	cout << ans;
}