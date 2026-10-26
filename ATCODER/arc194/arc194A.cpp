#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000];
ll mx[200000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	if (N == 1) {
		cout << A[0];
		return;
	}
	ll omx = 0, emx = A[0];
	for (int i = 0; i < N; ++i) {
		if (i == 0) {
			mx[i] = A[i];
			emx = A[0];
			continue;
		}
		if (i == 1) {
			mx[i] = A[0] + A[1];
			omx = max(0ll, mx[i]);
			continue;
		}
		if (i % 2) {
			mx[i] = A[i] + emx;
			omx = max(omx, mx[i]);
		} else {
			mx[i] = A[i] + omx;
			emx = max(emx, mx[i]);
		}
	}
	ll ans = 0;
	for (int i = 0; i < N; ++i) ans += A[i];
	for (int i = N - 1; i >= 0; i -= 2) ans = max(ans, mx[i]);
	if (N % 2 == 0) ans = max(ans, 0ll);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}