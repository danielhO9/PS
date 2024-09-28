#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, W;
ll hap[3001][3001];

void solve() {
	cin >> N >> W;
	for (int i = 0; i < N; ++i) {

		ll w, v; cin >> w >> v;
		for (int j = W; j >= 0; --j) {
			hap[i + 1][j] = hap[i][j];
			ll cur = v - 1;
			ll added = 0ll;
			for (int k = j + w; k <= W; k += w) {
				added += cur;
				cur -= 2;
				if (hap[i + 1][k] >= hap[i][j] + added) break;
				hap[i + 1][k] = hap[i][j] + added;
			}
		}
		
		for (int j = 1; j <= W; ++j) hap[i + 1][j] = max(hap[i + 1][j], hap[i + 1][j - 1]);
	}
	cout << hap[N][W];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}