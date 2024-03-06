#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int N, C; cin >> N >> C;
	int arr[N]; for (int i = 0; i < N; ++i) cin >> arr[i];
	vector<int> L, R;
	L.push_back(0); R.push_back(0);
	for (int i = 0; i < N / 2; ++i) {
		int s = L.size();
		for (int j = 0; j < s; ++j) if (arr[i] + L[j] <= C) L.push_back(arr[i] + L[j]);
	}
	for (int i = N / 2; i < N; ++i) {
		int s = R.size();
		for (int j = 0; j < s; ++j) if (arr[i] + R[j] <= C) R.push_back(arr[i] + R[j]);
	}
	sort(L.begin(), L.end()); sort(R.begin(), R.end());
	ll ans = 0; ll p = (ll) R.size() - 1;
	for (ll i = 0; i < L.size(); ++i) {
		while (L[i] + R[p] > C) --p;
		ans += (p + 1);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}