#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cache[21][100];
vector<int> num;

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		int tmp; cin >> tmp;
		num.push_back(tmp);
	}
	memset(cache, 0, sizeof(cache));
	cache[num[0]][0] = 1;
	for (int i = 1; i < (int)num.size() - 1; ++i) {
		for (int j = 0; j <= 20; ++j) {
			int nj = j + num[i];
			if (0 <= nj && nj <= 20) {
				cache[nj][i] += cache[j][i - 1];
			}
			nj = j - num[i];
			if (0 <= nj && nj <= 20) {
				cache[nj][i] += cache[j][i - 1];
			}
		}
	}
	cout << cache[num.back()][(int)num.size() - 2];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}