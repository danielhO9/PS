#include <bits/stdc++.h>
using namespace std;

int n, r;
unordered_map<string, int> station;
unordered_map<string, int> feat;
int cur = 0;
int cnt[512];
int cf[500000];

int func(string& s, bool q) {
	int ans = 0;
	string tmp;
	for (auto i: s) {
		if (i == ',') {
			if (feat.find(tmp) == feat.end()) {
				if (q) return -1;
				else feat[tmp] = cur++;
			}
			ans += (1 << feat[tmp]);
			tmp = "";
		} else tmp += i;
	}
	if (feat.find(tmp) == feat.end()) {
		if (q) return -1;
		else feat[tmp] = cur++;
	}
	ans += (1 << feat[tmp]);
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		station[s] = i;
	}
	cnt[0] = n;
	cin >> r;
	for (int i = 0; i < r; ++i) {
		char t; cin >> t;
		if (t == 'U') {
			string s; cin >> s;
			int snum = station[s];
			string f; cin >> f;
			int val = func(f, 0);
			--cnt[cf[snum]];
			cf[snum] = val;
			++cnt[cf[snum]];
		} else {
			string f; cin >> f;
			int val = func(f, 1);
			if (val == -1) {
				cout << 0 << '\n';
				continue;
			}
			int ans = 0;
			for (int i = 0; i < 512; ++i) {
				bool flag = true;
				for (int j = 0; j < 9; ++j) if ((val >> j) & 1) {
					if (!((i >> j) & 1)) flag = false;
				}
				if (flag) ans += cnt[i];
			}
			cout << ans << '\n';
		}
	}

}