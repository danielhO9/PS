#include <bits/stdc++.h>
using namespace std;

int a, b, c;

void solution() {
	cin >> a >> b >> c;
	if ((b + c) % 2 == 0) cout << 1 << " ";
	else cout << 0 << " ";
	if ((c + a) % 2 == 0) cout << 1 << " ";
	else cout << 0 << " ";
	if ((a + b) % 2 == 0) cout << 1;
	else cout << 0;
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solution();
}