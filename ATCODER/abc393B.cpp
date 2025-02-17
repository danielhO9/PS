#include <bits/stdc++.h>
using namespace std;

int acnt[100];
int ccnt[100];
string s;

void solve() {
	cin >> s;
	acnt[0] = (s[0] == 'A');
	ccnt[0] = (s[0] == 'C');
	for (int i = 1; i < s.size(); ++i) {
		acnt[i] = acnt[i - 1] + (s[i] == 'A');
		ccnt[i] = ccnt[i - 1] + (s[i] == 'C');
	}
	int ans = 0;
	for (int i = 0; i < s.size(); ++i) if (s[i] == 'B') {
		for (int j = 0; j < i; ++j) if (s[j] == 'A') {
			int k = i + (i - j);
			if (s[k] == 'C') ++ans;
		}
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}