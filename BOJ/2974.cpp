#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL A, B, ans, cache[18][30][19][13][11], tenTimes[19];
int p[4] = {2, 3, 5, 7};
int pc[4] = {0, 0, 0, 0};
int num[10][4] = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
   	{ 1, 0, 0, 0 },
   	{ 0, 1, 0, 0 },
   	{ 2, 0, 0, 0 },
   	{ 0, 0, 1, 0 },
   	{ 1, 1, 0, 0 },
   	{ 0, 0, 0, 1 },
   	{ 3, 0, 0, 0 },
   	{ 0, 2, 0, 0 }
};

LL makeNum(LL n, int t, LL l, LL r) {
	if (n + tenTimes[t + 1] - 1 < l || r < n) return 0;
	if (t == -1) {
		for (int i = 0; i < 4; ++i) if (pc[i] != 0) return 0;
		return 1;
	}
	if (l <= n && n + tenTimes[t + 1] - 1 <= r && cache[t][pc[0]][pc[1]][pc[2]][pc[3]] != -1) return cache[t][pc[0]][pc[1]][pc[2]][pc[3]];
	LL ret = 0; bool avail;
	for (LL i = (n != 0); i < 10; ++i) {
		avail = true;
		for (int j = 0; j < 4; ++j) {
			pc[j] -= num[i][j];
			if (pc[j] < 0) avail = false;
		}
		if (avail) ret += makeNum(n + i * tenTimes[t], t - 1, l, r);
		for (int j = 0; j < 4; ++j) pc[j] += num[i][j];
	}
	if (l <= n && n + tenTimes[t + 1] - 1 <= r) cache[t][pc[0]][pc[1]][pc[2]][pc[3]] = ret;
	return ret;
}

void makeCases(LL n, int t) {
	if (t == 4) {
		ans += makeNum(0, 17, (A + n - 1) / n, B / n);
		return;
	}
	makeCases(n, t + 1);
	if (n * p[t] <= 1e9 && n * n * p[t] * p[t] <= B) {
		++pc[t]; makeCases(n * p[t], t); --pc[t];
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> A >> B;
	memset(cache, -1, sizeof(cache));
	tenTimes[0] = 1LL;
	for (int i = 1; i < 19; ++i) tenTimes[i] = tenTimes[i - 1] * 10;
	makeCases(1, 0);
	cout << ans;
}