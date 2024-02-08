#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

vector<LL> dict[100001];
LL cnt[100001], n, a[80000], already[100001];

void init() {
	LL temp;
	for (LL i = 1; i <= 100000; ++i) {
		for (LL j = 1; j <= 100000; ++j) {
			if (j * j == i) {
				dict[i].push_back(j);
				break;
			} else if (j * j > i) break;
			else if (i % j == 0) {
				dict[i].push_back(j);
				dict[i].push_back(i / j);
			}
		}
		if (i == 1) cnt[i] = 1;
		else {
			temp = 0;
			for (auto j: dict[i]) if (j != i) temp += cnt[j];
			cnt[i] = i - temp;
		}
	}
}

void solution() {
	LL ret = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	sort(a, a + n);
	memset(already, 0, sizeof(already));
	for (int i = 0; i < n - 1; ++i) {
		if (i != 0) for (auto j: dict[a[i]]) ret += cnt[j] * already[j] * (n - 1 - i);
		for (auto j: dict[a[i]]) ++already[j];
	}
	cout << ret << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	init();
	while (t--) solution();
}