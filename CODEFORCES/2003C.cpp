#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;
int cnt[26];

void solve() {
	cin >> n;
	cin >> s;
	memset(cnt, 0, sizeof(cnt));
	for (auto i: s) ++cnt[i - 'a'];
	int mcnt = 0, mchar = 0;
	for (int i = 0; i < 26; ++i) {
		if (cnt[i] > mcnt) {
			mcnt = cnt[i];
			mchar = i;
		}
	}
	string ret;
	ret += mchar + 'a';
	--cnt[mchar];
	while (true) {
		bool flag = false;
		for (int i = 0; i < 26; ++i) if (cnt[i] > 0 && ret.back() != i + 'a') {
			ret += i + 'a';
			--cnt[i];
			flag = true;
			break;
		}
		if (!flag) break;
	}
	for (int i = 0; i < 26; ++i) if (cnt[i] > 0) {
		while (cnt[i] > 0) {
			ret += 'a' + i;
			--cnt[i];
		}
	}
	cout << ret << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}