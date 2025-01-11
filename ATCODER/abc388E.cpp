#include <bits/stdc++.h>
using namespace std;

int N;
int A[500000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	int l = 0, r = (N + 1) / 2 + 1, mid;
	while (l + 1 < r) {
		mid = (l + r) / 2;
		bool flag = true;
		for (int i = 0; i < mid; ++i) if (A[i] * 2 > A[N - mid + i]) flag = false;
		if (flag) l = mid;
		else r = mid;
	}
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}