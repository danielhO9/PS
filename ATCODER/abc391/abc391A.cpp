#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string s; cin >> s;
	if (s == "N") cout << 'S';
	if (s == "E") cout << 'W';
	if (s == "W") cout << 'E';
	if (s == "S") cout << 'N';
	if (s == "NE") cout << "SW";
	if (s == "NW") cout << "SE";
	if (s == "SE") cout << "NW";
	if (s == "SW") cout << "NE";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}