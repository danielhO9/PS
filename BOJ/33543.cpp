#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[250000], B[250000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	vector<ll> v, sm;
	ll ans = 0;
	for (int i = 0; i < N; ++i) cin >> A[i] >> B[i];
	for (int i = 0; i < N; ++i) v.push_back(A[i] - B[i]);
	for (int i = 0; i < N; ++i) ans += max(A[i], B[i]);
	sort(v.begin(), v.end());
	sm.resize(v.size());
	for (int i = 0; i < N; ++i) {
		if (i) sm[i] = sm[i - 1] + v[i];
		else sm[i] = v[i];
	}
	ll prv = 0;
	int Q; cin >> Q;
	while (Q--) {
		char c; ll X; cin >> c >> X;
		if (c == 'A') {
			auto idx = lower_bound(v.begin(), v.end(), -prv) - v.begin();
			ans += X * (N - idx);
			auto nidx = lower_bound(v.begin(), v.end(), -prv - X) - v.begin();
			ans += ((idx == 0 ? 0 : sm[idx - 1]) - (nidx == 0 ? 0 : sm[nidx - 1])) + (X + prv) * (idx - nidx);
		} else {
			auto idx = upper_bound(v.begin(), v.end(), -prv) - v.begin(); --idx;
			ans += X * (idx + 1);
			auto nidx = upper_bound(v.begin(), v.end(), -prv + X) - v.begin(); --nidx;
			ans += -((nidx == -1 ? 0 : sm[nidx]) - (idx == -1 ? 0 : sm[idx])) + (X - prv) * (nidx - idx);
		}
		cout << ans << '\n';
		prv += (c == 'A' ? X : -X);
	}
}

/*
-4 -1 5
-2 1 7
prv: 2
19 -> 20
*/

/*
A X
Ai >= Bi -> +X
Ai < Bi, Ai + X >= Bi : Ai + X - Bi
Ai + X < Bi : 0

B X
Ai <= Bi -> +X
Ai > Bi, Ai <= Bi + X : Bi + X - Ai
Ai > Bi + X : 0
*/