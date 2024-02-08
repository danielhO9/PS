#include <bits/stdc++.h>
using namespace std;

int N, x[15], s[30], m[30], ans;

void solution(int y) {
	if (y == N) { ++ ans; return; }
	for (int i = 0; i < N; ++i) {
		if (x[i] == 0 && s[i + y] == 0 && m[i - y + 15] == 0) {
			x[i] = 1; s[i + y] = 1; m[i - y + 15] = 1;
			solution(y + 1);
			x[i] = 0; s[i + y] = 0; m[i - y + 15] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; solution(0);
	cout << ans;
}