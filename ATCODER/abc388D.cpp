#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[500000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	vector<ll> get(N, 0);
	ll cur = 0;
	for (int i = 0; i < N; ++i) {
		cur += get[i];
		A[i] += cur;
		
		// A[i]
		++get[i + 1];
		if (i + A[i] + 1 < N) --get[i + A[i] + 1];

		A[i] -= ((N - 1) - (i + 1) + 1);
		A[i] = max(0ll, A[i]);
		// for (int i = 0; i < N; ++i) cout << get[i] << ' ';
		// cout << '\n';
	}
	for (int i = 0; i < N; ++i) cout << A[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}