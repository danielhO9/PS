#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	int g = 0;
	bool flag = true;
	for (int i = 0; i < N; ++i) {
		int P; cin >> P;
		g ^= P;
		if (P != 1) flag = false;
	}
	if (flag) {
		if (N % 2) cout << "cubelover";
		else cout << "koosaga";
		return;
	}
	if (g == 0) cout << "cubelover";
	else cout << "koosaga";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}