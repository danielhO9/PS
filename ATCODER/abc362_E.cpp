#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[80];
ll ans[81];
unordered_map<ll, vector<int>> M;
vector<ll> now;
const ll MOD = 998244353;

ll comb[81][81];

void init() {
	for (int i = 1; i <= N; ++i) comb[i][0] = 1ll;
	for (int i = 1; i <= N; ++i) comb[i][i] = 1ll;
	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j < i; ++j) {
			comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
			comb[i][j] %= MOD;
			// cout << comb[i][j] << ' ';
		}
	}
}

void construct(int last) {
	// for (auto i: now) cout << i << ' ';
	// cout << '\n';
	if (now.size() <= 1) {
		for (int i = last + 1; i < N; ++i) {
			if (!now.empty() && now.back() == A[i]) continue;
			now.push_back(A[i]);
			++ans[now.size()];
			ans[now.size()] %= MOD;
			construct(i);
			now.pop_back();
		}
		return;
	}
	ll dif = now[1] - now[0];
	ll num = now.back() + dif;
	if (M.find(num) == M.end()) return;
	auto iter = lower_bound(M[num].begin(), M[num].end(), last + 1) - M[num].begin();
	for (int i = iter; i < M[num].size(); ++i) {
		now.push_back(A[M[num][i]]);
		++ans[now.size()];
		ans[now.size()] %= MOD;
		construct(M[num][i]);
		now.pop_back();
	}
}

void solve() {
	cin >> N;
	init();
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		M[A[i]].push_back(i);
	}
	for (auto [_, arr]: M) {
		int sz = arr.size();
		if (sz >= 2) {
			for (int i = 2; i <= sz; ++i) {
				ans[i] += comb[sz][i];
				ans[i] %= MOD;
			}
		}
	}
	construct(-1);
	for (int i = 1; i <= N; ++i) cout << ans[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}