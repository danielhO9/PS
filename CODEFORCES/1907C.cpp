#include <bits/stdc++.h>
using namespace std;

int n;
string s;
int cache[26];

int solution() {
	cin >> n; cin >> s;
	memset(cache, 0, sizeof(cache));
	for (int i = 0; i < n; ++i) ++cache[s[i] - 'a'];
	int m = 0;
	for (int i = 0; i < 26; ++i) m = max(m, cache[i]);
	return max(n % 2, m - (n - m));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) cout << solution() << '\n';
}