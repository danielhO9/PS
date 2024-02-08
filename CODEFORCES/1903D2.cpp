#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, q;
LL a[1000000], k, asum, lsum, dpsum[1LL << 20][20], dpcnt[1LL << 20LL];

void solution() {
	cin >> k;
	if (k >= lsum) {
		k += asum;
		cout << k / n << '\n';
		return;
	}
	LL ret = 0;
	for (int i = 19; i >= 0; --i) {
		LL x = (n - dpcnt[ret | (1 << i)]) * (1 << i);
		x -= dpsum[ret][i] - dpsum[ret | (1 << i)][i];
		if (x <= k) {
			k -= x;
			ret |= (1 << i);
		}
 	}
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		asum += a[i];
		lsum += (1LL << 20LL) - a[i];
		++dpcnt[a[i]];
		LL sum = 0;
		for (int j = 0; j < 20; ++j) {
			sum += a[i] & (1LL << j);
			dpsum[a[i]][j] += sum;
		}
	}
	for (int i = 0; i < 20; ++i) for (int j = 0; j < (1 << 20); ++j) if (!(j & (1 << i))) dpcnt[j] += dpcnt[j + (1 << i)];
	for (int i = 0; i < 20; ++i) for (int j = 0; j < (1 << 20); ++j) if (!(j & (1 << i))) {
		for (int l = 0; l < 20; ++l) dpsum[j][l] += dpsum[j + (1 << i)][l];
	}
	for (int i = 0; i < q; ++i) solution();
}