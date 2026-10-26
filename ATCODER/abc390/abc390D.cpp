#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[12], sm[12];
unordered_set<ll> ans;

void dfs(int idx, int sz, ll val) {
	if (idx == N) {
		ans.insert(val);
		return;
	}
	ll nval;
	for (int i = 0; i <= sz; ++i) {
		nval = val;
		nval ^= sm[i];
		sm[i] += A[idx];
		nval ^= sm[i];
		if (i < sz) dfs(idx + 1, sz, nval);
		else dfs(idx + 1, sz + 1, nval);
		sm[i] -= A[idx];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	dfs(0, 0, 0);
	cout << ans.size();
}