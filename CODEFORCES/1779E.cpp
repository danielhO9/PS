#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

int query(int m, string& s) {
	cout << "? " << m << ' ' << s << '\n';
	cout.flush();
	int ret; cin >> ret;
	return ret;
}

void solve() {
	cin >> n;
	vector<pair<int, int>> v;
	for (int i = 1; i <= n; ++i) {
		string s;
		for (int j = 1; j <= n; ++j) {
			if (i == j) s.push_back('0');
			else s.push_back('1');
		}
		int q = query(i, s);
		v.push_back({-q, i});
	}
	sort(v.begin(), v.end());
	bool cm[n + 1]; memset(cm, 0, sizeof(cm)); cm[v[0].second] = true;
	for (int i = 1; i < n; ++i) {
		int cur = v[i].second;
		string s;
		for (int j = 1; j <= n; ++j) s += cm[j] + '0';
		int q = query(cur, s);
		if (q > 0) {
			for (int j = i; j >= 0; --j) {
				if (cm[v[j].second]) break;
				cm[v[j].second] = true;
			}
		}
	}
	cout << "! ";
	string ans;
	for (int i = 1; i <= n; ++i) ans += cm[i] + '0';
	cout << ans << '\n';
	cout.flush();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; t = 1;
	while (t--) solve();
}