#include <bits/stdc++.h>
using namespace std;

void solve() {
	set<int> x, y;
	for (int i = 0; i < 4; ++i) {
		int xi, yi; cin >> xi >> yi;
		x.insert(xi); y.insert(yi);
	}
	cout << (*(next(y.begin())) - *(y.begin())) * (*(next(x.begin())) - *(x.begin())) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}