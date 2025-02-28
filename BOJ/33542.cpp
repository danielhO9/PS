#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A, B;
ll N;
ll L[500000], R[500000];
const ll MAX = 3e8 + 1;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> A >> B >> N;
	for (ll i = 0; i < N; ++i) cin >> L[i] >> R[i];
	if (A < B) {
		cout << -1 << ' ' << -1;
		return 0;
	}
	vector<pair<ll, ll>> v;
	for (ll i = 0; i < N; ++i) v.push_back({R[i], i});
	sort(v.begin(), v.end());
	pair<ll, ll> ans = {-1, -1};
	ll val = MAX ;
	for (ll i = 0; i < N; ++i) {
		ll a = L[i];
		if (B + a > A) {
			if (B + a < val) {
				ans = {i + 1, -1};
				val = B + a;
			}
			continue;
		}
		auto idx = lower_bound(v.begin(), v.end(), make_pair(A - B - a + 1, 0ll)) - v.begin();
		if (idx == N) continue;
		if (v[idx].second == i) ++idx;
		if (idx == N) continue;
		ll b = v[idx].first;
		if (B + a + b < val) {
			ans = {i + 1, v[idx].second + 1};
			val = B + a + b;
		}
	}
	v.clear();
	for (int i = 0; i < N; ++i) v.push_back({L[i], i});
	sort(v.begin(), v.end());
	for (ll i = 0; i < N; ++i) {
		ll b = R[i];
		if (B + b > A) {
			if (B + b < val) {
				ans = {-1, i + 1};
				val = B + b;
			}
			continue;
		}
		auto idx = lower_bound(v.begin(), v.end(), make_pair(A - B - b + 1, 0ll)) - v.begin();
		if (idx == N) continue;
		if (v[idx].second == i) ++idx;
		if (idx == N) continue;
		ll a = v[idx].first;
		if (B + a + b < val) {
			ans = {v[idx].second + 1, i + 1};
			val = B + a + b;
		}
	}
	if (val == MAX) cout << "No";
	else cout << ans.first << ' ' << ans.second;
}