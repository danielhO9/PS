#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int H[200002];
ll cnt[200002];

void add(int a, int b) {
	if (a > b) return;
	// cout << a << ' ' << b << '\n';
	++cnt[a];
	--cnt[b + 1];
}

void solve() {
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> H[i];
	vector<pair<int, int>> v;
	for (int i = 1; i <= N; ++i) {
		v.push_back({H[i], i});
	}
	sort(v.begin(), v.end());
	set<int> s;
	for (int i = N - 1; i >= 0; --i) {
		int idx = v[i].second;
		if (s.empty()) {
			add(1, idx - 1);
			s.insert(idx);
			continue;
		}
		s.insert(idx);
		auto itr = s.lower_bound(idx);
		if (itr == s.begin()) {
			add(1, idx - 1);
		} else {
			--itr;
			// cout << *itr << ' '<< idx << "\n";
			add(*itr, idx - 1);
		}
	}
	ll tmp = 0;
	for (int i = 1; i <= N; ++i) {
		tmp += cnt[i];
		cout << tmp << ' ';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}