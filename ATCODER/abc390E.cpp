#include <bits/stdc++.h>
using namespace std;

int N, X;
int V[5000], A[5000], C[5000];
int cache[3][5001];

void solve() {
	cin >> N >> X;
	for (int i = 0; i < N; ++i) cin >> V[i] >> A[i] >> C[i];
	for (int i = 0; i < N; ++i) --V[i];
	for (int i = 0; i < N; ++i) {
		for (int j = X; j >= C[i]; --j) cache[V[i]][j] = max(cache[V[i]][j], cache[V[i]][j - C[i]] + A[i]);
	}
	int l = 0, r = 1e9 + 1, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		int sc = 0;
		for (int i = 0; i < 3; ++i) {
			sc += lower_bound(cache[i], cache[i] + X + 1, mid) - cache[i];
		}
		if (sc <= X) l = mid;
		else r = mid;
	}
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}