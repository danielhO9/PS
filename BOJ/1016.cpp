#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	LL minx, maxx; cin >> minx >> maxx;
	bool nn[maxx - minx + 1]; memset(nn, 0, sizeof(nn));
	for (LL i = 2; i <= 1e6; ++i) {
		LL square = i * i;
		for (LL j = square * ((minx + square - 1) / square); j <= maxx; j += square) {
			nn[j - minx] = 1;
		}
	}
	LL ans = 0;
	for (auto i: nn) if (i == 0) ++ans;
	cout << ans;
}