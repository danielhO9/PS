#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int N; cin >> N;
	vector<ll> minus, plus;
	bool zero = false;
	ll ret = 0;
	for (int i = 0; i < N; ++i) {
		ll num; cin >> num;
		if (num < 0) minus.push_back(num);
		else if (num == 0) zero = true;
		else if (num > 1) plus.push_back(num);
		else ret += 1;
	}
	sort(minus.begin(), minus.end());
	sort(plus.begin(), plus.end(), [] (const ll& a, const ll& b) {
		return a > b;
	});
	for (int i = 0; i + 1 < minus.size(); i += 2) {
		ret += minus[i] * minus[i + 1];
	}
	for (int i = 0; i + 1 < plus.size(); i += 2) {
		ret += plus[i] * plus[i + 1];
	}
	if (minus.size() % 2 && !zero) ret += minus.back();
	if (plus.size() % 2) ret += plus.back();
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}