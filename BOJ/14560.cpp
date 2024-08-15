#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, D;
ll A[30];

vector<ll> merge_three(int s, int e) {
	if (s + 1 == e) {
		return {-A[s], 0, A[s]};
	}
	vector<ll> v2 = merge_three(s + 1, e);
	vector<ll> v1 = v2, v3 = v2;
	for (auto& i: v1) i -= A[s];
	for (auto& i: v3) i += A[s];
	vector<ll> tmp; tmp.resize(v1.size() + v2.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), tmp.begin());
	vector<ll> ret; ret.resize(tmp.size() + v3.size());
	merge(tmp.begin(), tmp.end(), v3.begin(), v3.end(), ret.begin());
	return ret;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	cin >> D;
	if (N == 1) {
		cout << 1 + 2 * (A[0] <= D);
		return;
	}
	auto lhalf = merge_three(0, N / 2);
	auto rhalf = merge_three(N / 2, N);
	ll ans = 0ll;

	ll l = 0;
	ll r = 0;
	for (auto i: lhalf) {
		// cout << l << ' ' << r << '\n';
		while (r < rhalf.size() && rhalf[r] - i <= D) ++r;
		while (l < rhalf.size() && i - rhalf[l] > D) ++l;
		ans += r - l;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
}