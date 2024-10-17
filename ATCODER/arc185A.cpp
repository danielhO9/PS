#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;

void solve() {
	cin >> N >> M;
	ll sum = (N + 1) * N / 2;
	ll y = (2 * sum) % M;
	if (1 <= y && y <= N) cout << "Bob\n";
	else cout << "Alice\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}