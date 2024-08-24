#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	int A[N]; for (int i = 0; i < N; ++i) cin >> A[i];
	sort(A, A + N);
	int sum = 0;
	for (int i = 0; i < N; ++i) sum += A[i];
	if (sum - A[N - 1] < A[N - 1]) {
		cout << sum - A[N - 1];
	} else {
		cout << sum / 2;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}