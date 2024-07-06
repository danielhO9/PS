#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, M, K; cin >> N >> M >> K;
	while (K) {
		if (N / 2 < M) --M;
		else --N;
		--K;
	}
	cout << min(N / 2, M);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}