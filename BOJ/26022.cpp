#include <bits/stdc++.h>
using namespace std;

int l, w, n;
char alpha[26][26];

void solve() {
	cin >> l >> w >> n;
	if ((l * w) % n != 0) {
		cout << "impossible";
		return;
	}
	int ll = l, ww = w, nn = n;
	while (n != 1) {
		for (int i = 2; i <= n; ++i) if (n % i == 0) {
			if (l % i == 0) {
				l /= i;
				n /= i;
				break;
			}
			if (w % i == 0) {
				w /= i;
				n /= i;
				break;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < ll / l; ++i) for (int j = 0; j < ww / w; ++j) alpha[i][j] = 'A' + (cnt++);
	for (int i = 0; i < ll; ++i) {
		for (int j = 0; j < ww; ++j) {
			cout << alpha[i / l][j / w];
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}