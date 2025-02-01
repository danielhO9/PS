#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, K;
ll A[200000], B[200000], C[200000];

ll f(ll x) {
	ll cnt = 0;
	for (int i = 0; i < N; ++i) {
		if (A[i] * B[0] + B[0] * C[0] + C[0] * A[i] < x || cnt >= K) break;
		for (int j = 0; j < N; ++j) {
			if (A[i] * B[j] + B[j] * C[0] + C[0] * A[i] < x || cnt >= K) break;
			for (int k = 0; k < N; ++k) {
				if (A[i] * B[j] + B[j] * C[k] + C[k] * A[i] >= x) ++cnt;
				else break;
				if (cnt >= K) break;
			}
		}
	}
	return cnt;
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) cin >> B[i];
	for (int i = 0; i < N; ++i) cin >> C[i];
	sort(A, A + N); sort(B, B + N); sort(C, C + N);
	reverse(A, A + N); reverse(B, B + N); reverse(C, C + N);
	ll l = 0, r = 3e18, mid;
	++r;
	// cout << r << "\n";
	while (l + 1 < r) {
		mid = (l + r) / 2;
		if (f(mid) >= K) l = mid;
		else r = mid;
	}
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}