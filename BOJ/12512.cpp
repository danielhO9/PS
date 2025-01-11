#include <bits/stdc++.h>
using namespace std;

int val[26][26];
bool clr[26][26];
int C, D, N;

void solve() {
	memset(val, -1, sizeof(val));
	memset(clr, 0, sizeof(clr));
	string tar;
	cin >> C;
	vector<string> c(C);
	for (int i = 0; i < C; ++i) cin >> c[i];
	for (int i = 0; i < C; ++i) {
		val[c[i][0] - 'A'][c[i][1] - 'A'] = c[i][2] - 'A';
		val[c[i][1] - 'A'][c[i][0] - 'A'] = c[i][2] - 'A';
	}
	cin >> D;
	vector<string> d(D);
	for (int i = 0; i < D; ++i) cin >> d[i];
	for (int i = 0; i < D; ++i) {
		clr[d[i][0] - 'A'][d[i][1] - 'A'] = true;
		clr[d[i][1] - 'A'][d[i][0] - 'A'] = true;
	}
	vector<char> ans;
	vector<int> cnt(26, 0);
	cin >> N >> tar;
	for (auto i: tar) {
		// for (auto j: ans) cout << j << ' ';
		// cout << '\n';
		if (ans.size() == 0) {
			ans.push_back(i);
			++cnt[i - 'A'];
		}
		else {
			if (val[ans.back() - 'A'][i - 'A'] == -1) {
				ans.push_back(i);
				++cnt[i - 'A'];
			}
			else {
				char tmp = val[ans.back() - 'A'][i - 'A'] + 'A';
				--cnt[ans.back() - 'A'];
				ans.pop_back();
				ans.push_back(tmp);
				++cnt[tmp - 'A'];
			}
		}
		for (int j = 0; j < 26; ++j) for (int k = 0; k < 26; ++k) if (cnt[j] > 0 && cnt[k] > 0) {
			if (clr[j][k]) {
				ans.clear();
				for (int l = 0; l < 26; ++l) cnt[l] = 0;
			}
		}
	}
	cout << "[";
	for (int i = 0; i < ans.size(); ++i) {
		cout << ans[i];
		if (i + 1 != ans.size()) cout << ", ";
	}
	cout << "]\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
}