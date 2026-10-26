#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	ll left = 0ll;
	ll sum = A[0];
	for (int i = 1; i < N; ++i) {
		ll last = (sum + i - 1) / i;
		if (last <= A[i]) {
			ll dif = min(left, A[i] - last);
			A[i] -= dif;
			left -= dif;
			sum += A[i];
		} else {
			left += last - A[i];
			A[i] = last;
			sum += A[i];
		}
	}
	if (left == 0) cout << "Yes\n";
	else cout << "No\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}