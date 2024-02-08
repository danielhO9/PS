#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	vector<LL> binary(30);
	LL N; cin >> N; LL ans = 0;
	LL pre = 0;
	for (LL i = 1; i <= N; ++i) {
		LL temp; cin >> temp;
		pre ^= temp;
		for (LL j = 0; j < 30; ++j) {
			if ((pre >> j) & 1) {
				ans += (i - binary[j]) << j;
				++binary[j];
			} else {
				ans += binary[j] << j;
			}
		}
	}
	cout << ans;
}