#include <bits/stdc++.h>
using namespace std;

void solve() {
	string s1, s2; cin >> s1 >> s2;
	if (s1 == "fine" && s2 == "sick") cout << 3;
	else if (s1 == "sick" && s2 == "fine") cout << 2;
	else if (s1 == "fine") cout << 4;
	else cout << 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}