#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	int A[N]; for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N - 2; ++i) if (A[i] == A[i + 1] && A[i + 1] == A[i + 2]) {
		cout << "Yes";
		return;
	}
	cout << "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}