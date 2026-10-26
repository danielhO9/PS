#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	cout << (s[0] - '0') * (s[2] - '0');
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}