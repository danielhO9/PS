#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<ll> idx[300001];

ll f(vector<int>& x) {
	ll ret = 0;
	for (int i = 0; i + 1 < x.size(); ++i) {
		ll tmp = x[i + 1] - x[i];
		ret += tmp * (tmp + 1) / 2;
	}
	return ret;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int A; cin >> A;
		idx[A].push_back(i);
	}
	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		vector<int> tmp;
		tmp.push_back(-1);
		for (auto j: idx[i - 1]) tmp.push_back(j);
		tmp.push_back(N);
		ans += f(tmp);
		for (auto j: idx[i]) tmp.push_back(j);
		sort(tmp.begin(), tmp.end());
		ans -= f(tmp);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}