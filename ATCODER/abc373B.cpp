#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
int idx[26];

void solve() {
	cin >> s;
	for (int i = 0; i < 26; ++i) {
		idx[s[i] - 'A'] = i;
	}
	int ans = 0;
	for (int i = 0; i < 25; ++i) {
		ans += abs(idx[i] - idx[i + 1]);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}