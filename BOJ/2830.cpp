#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	LL N; cin >> N;
	vector<LL> binary(20);
	for (int i = 0; i < N; ++i) {
		LL name; cin >> name;
		for (int j = 0; j < 20; ++j) {
			if ((name >> j) & 1) ++binary[j];
		}
	}
	LL ans = 0;
	for (int i = 0; i < 20; ++i) {
		ans += (binary[i] * (N - binary[i])) << i;
	}
	cout << ans;
}