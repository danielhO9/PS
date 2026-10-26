#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;

void solve() {
	cin >> s;
	int n = s.size();
	cout << 1 << ' ' << n << ' ';
	int zero = -1;
	for (int i = 0; i < n; ++i) if (s[i] == '0') {
		zero = i;
		break;
	}
	if (zero == -1) {
		cout << 1 << ' ' << 1 << '\n';
		return;
	}
	int mxcnt = -1;
	int mxs = -1;
	for (int i = 0; i < zero; ++i) {
		int cnt = 0;
		for (int j = 0; j < n - zero; ++j) {
			int sidx = zero + j;
			int ssidx = j + i;
			if (s[sidx] != s[ssidx]) ++cnt;
			else break;
		}
		if (cnt > mxcnt) {
			mxcnt = cnt;
			mxs = i;
		}
	}
	cout << mxs + 1 << ' ' << mxs + n - zero << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}