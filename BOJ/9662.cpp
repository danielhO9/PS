#include <bits/stdc++.h>
using namespace std;

int M;
int K;
vector<int> k;
int cache[1 << 22];
int nxt[1 << 22];

int val[23];

void solve() {
	memset(cache, -1, sizeof(cache));
	cin >> M;
	cin >> K;
	for (int i = 0; i < K; ++i) {
		int tmp; cin >> tmp;
		k.push_back(tmp);
	}
	val[0] = 0;
	for (int i = 1; i <= 22; ++i) {
		bool flag = false;
		for (auto j: k) if (i >= j) {
			if (val[i - j] == 0) {
				flag = true;
				break;
			}
		}
		if (flag) val[i] = 1;
		else val[i] = 0;
	}

	int ans = 0;
	for (int i = 1; i <= 22; ++i) if (val[i] == 0) ++ans;
	if (M <= 22) {
		ans = 0;
		for (int i = 1; i <= M; ++i) if (val[i] == 0) ++ans;
		cout << ans;
		return;
	}
	
	int num = 0;
	for (int i = 0; i < 22; ++i) if (val[22 - i] == 1) num += (1 << i);
	int s = num;
	int cs;
	while (true) {
		bool flag = false;
		for (auto i: k) {
			--i;
			if (!((num >> i) & 1)) {
				flag = true;
				break;
			}
		}
		if (flag) cache[num] = 1;
		else cache[num] = 0;

		int nnum = num;
		if (nnum >= (1 << 21)) nnum -= (1 << 21);
		nnum *= 2; nnum += cache[num];
		nxt[num] = nnum;
		if (cache[nnum] != -1) {
			cs = nnum;
			break;
		}
		num = nnum;
	}
	int cur = 23;
	num = s;
	while (true) {
		if (num == cs) break;
		if (cache[num] == 0) ++ans;
		if (num == M) {
			cout << ans;
			return;
		}
		++cur;
		num = nxt[num];
	}
	vector<int> v;
	while (true) {
		v.push_back(cache[num]);
		num = nxt[num];
		if (num == cs) break;
	}
	M -= cur;
	int sum = 0;
	for (auto i: v) sum += (1 - i);
	ans += sum * (M / v.size());
	M %= v.size();
	for (int i = 0; i <= M; ++i) ans += (1 - v[i]);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}