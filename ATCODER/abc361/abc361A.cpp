#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, K, X; cin >> N >> K >> X;
	vector<int> A(N);
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < K; ++i) cout << A[i] << ' ';
	cout << X << ' ';
	for (int i = K; i < N; ++i) cout << A[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}