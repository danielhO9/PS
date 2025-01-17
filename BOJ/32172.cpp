#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A[100001];
unordered_map<ll, bool> m;

void solve() {
	m[A[0]] = true;
	for (ll i = 1; i <= 100000; ++i) {
		if (A[i - 1] - i < 0 || m.find(A[i - 1] - i) != m.end()) A[i] = A[i - 1] + i;
		else A[i] = A[i - 1] - i;
		m[A[i]] = true;
	}
	int N; cin >> N;
	cout << A[N];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}