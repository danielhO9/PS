#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N; cin >> N;
	int g = 0;
	for (int i = 0; i < N; ++i) {
		int P; cin >> P;
		g ^= P;
	}
	if (g == 0) cout << "cubelover";
	else cout << "koosaga";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}