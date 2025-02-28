#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int X; cin >> X;
	for (int i = X + 1; i <= 9999; ++i) {
		int j = i / 100, k = i % 100;
		j += k;
		if (j * j == i) {
			cout << i;
			return 0;
		}
	}
	cout << -1;
}