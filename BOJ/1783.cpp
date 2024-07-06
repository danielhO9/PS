#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll N, M; cin >> N >> M;
	if (N == 1) {
		cout << 1;
		return;
	}
	if (N == 2) {
		cout << min(4ll, (M + 1) / 2);
		return;
	}
	if (M >= 7) cout << M - 2;
	else {
		cout << min(M, 4ll);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}