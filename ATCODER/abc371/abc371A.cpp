#include <bits/stdc++.h>
using namespace std;

void solve() {
	char a, b, c; cin >> a >> b >> c;
	if (a != b) {
		cout << "A";
	} else {
		if (a == '<') {
			if (c == '<') cout << "B";
			else cout << "C";
		} else {
			if (c == '>') cout << "B";
			else cout << "C";
		}
	}
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}