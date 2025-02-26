#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll L[2000];
unordered_map<ll, ll> cnt;
unordered_map<ll, ll> sm;
vector<pair<ll, ll>> v;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> L[i];
	// N = 2000;
	// for (int i = 0; i < N; ++i) L[i] = i + 1;
	for (int i = 0; i < N; ++i) ++cnt[L[i]];
	for (auto [i, j]: cnt) v.push_back({i, j});
	for (int i = 0; i < v.size(); ++i) {
		sm[v[i].first * 2] += v[i].first * v[i].first * (v[i].second / 2);
		for (int j = i + 1; j < v.size(); ++j) {
			sm[v[i].first + v[j].first] += v[i].first * v[j].first * min(v[i].second, v[j].second);
		}
	}
	ll ans = 0;
	for (auto [_, i]: sm) ans = max(ans, i);
	cout << ans;

}