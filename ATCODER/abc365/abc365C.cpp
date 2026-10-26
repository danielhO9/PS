#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll A[200000];

ll getVal(ll x) {
	ll ret = 0ll;
	for (int i = 0; i < N; ++i) {
		ret += min(A[i], x);
	}
	return ret;
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> A[i];
	ll sumA = 0ll;
	for (int i = 0; i < N; ++i) sumA += A[i];
	if (sumA <= M) {
		cout << "infinite";
		return;
	}
	ll l = 0, r = 1e9;
	while (l + 1 < r) {
		ll mid = (l + r) / 2;
		if (getVal(mid) <= M) l = mid;
		else r = mid;
	}
	cout << l;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}