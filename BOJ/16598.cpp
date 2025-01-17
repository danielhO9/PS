#include <bits/stdc++.h>
using namespace std;

int n, p;
bool d[2000000];

void solve() {
	cin >> n >> p;
	int ans = 0;
	int cnt = 0;
	int e = 0;
	for (int i = 0; i < n; ++i) {
		int tmp; cin >> tmp;
		d[tmp] = true;
	}
	for (int i = 0; i <= 1000000; ++i) {
		while (cnt < p || (cnt == p && d[e])) {
			if (!d[e]) ++cnt;
			++e;
		}
		ans = max(ans, e - i);
		if (!d[i]) --cnt;
	}
	cout << ans;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}