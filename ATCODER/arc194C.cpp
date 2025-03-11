#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
ll A[200000], B[200000], C[200000];
vector<ll> arr[3], sm[3];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) cin >> B[i];
	for (int i = 0; i < N; ++i) cin >> C[i];
	for (int i = 0; i < N; ++i) {
		if (A[i] == 0 && B[i] == 1) arr[0].push_back(C[i]);
		if (A[i] == 1 && B[i] == 0) arr[1].push_back(C[i]);
		if (A[i] == 1 && B[i] == 1) arr[2].push_back(C[i]);
	}
	for (int i = 0; i < 3; ++i) sort(arr[i].begin(), arr[i].end());
	for (int i = 0; i < 3; ++i) sm[i] = arr[i];
	for (int i = 0; i < 3; ++i) for (int j = 1; j < sm[i].size(); ++j) sm[i][j] += sm[i][j - 1];

	reverse(arr[2].begin(), arr[2].end());
	ll cnt = arr[0].size() + arr[1].size();
	ll tsm = sm[2].size() ? sm[2][(int)sm[2].size() - 1] : 0;
	ll val = tsm * cnt;
	for (int i = 0; i < 2; ++i) {
		if (i == 0) for (int j = 0; j < arr[0].size(); ++j) val += arr[i][j] * ((ll) arr[0].size() - j);
		else for (int j = 0; j + 1 < arr[1].size(); ++j) val += arr[i][j] * ((ll) arr[1].size() - j - 1);
	}
	ll ans = val;
	ll idx[2] = {(ll) arr[0].size() - 1, (ll) arr[1].size() - 1};
	for (int i = 0; i < arr[2].size(); ++i) {
		ll cur = arr[2][i];
		tsm -= cur; val += 2 * tsm;
		for (int j = 0; j < 2; ++j) while (idx[j] >= 0 && arr[j][idx[j]] >= cur) --idx[j];
		ll tcnt = idx[0] + idx[1] + 2;
		val -= tcnt * cur; val += cur;
		for (int j = 0; j < 2; ++j) if (idx[j] >= 0) val += sm[j][idx[j]];
		ans = min(ans, val);
		// cout << cur << ' ' << tcnt << ' ' << val << '\n';
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}