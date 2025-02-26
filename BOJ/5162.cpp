#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, Y, B;
ll J[50];
ll jj[20][50];
ll c[20], g[20];

void solve() {
	cin >> n >> Y >> B;
	for (int i = 0; i < Y; ++i) cin >> J[i];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < Y; ++j) cin >> jj[i][j];
		cin >> c[i] >> g[i];
	}
	ll ans = -1;
	ll curj[50];
	ll curc, curg;
	for (int i = 0; i < (1 << n); ++i) {
		memset(curj, 0, sizeof(curj));
		curc = 0;
		curg = 0;
		for (int j = 0; j < n; ++j) if ((i >> j) & 1) {
			curc += c[j];
			curg += g[j];
			for (int k = 0; k < Y; ++k) curj[k] += jj[j][k];
		}
		bool flag = true;
		for (int j = 0; j < Y; ++j) if (curj[j] < J[j]) {
			flag = false;
			break;
		}
		if (flag && curc <= B) ans = max(ans, curg);
	}
	if (ans != -1) cout << ans << '\n';
	else cout << "No selection.\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 1; i <= t; ++i) {
		cout << "Data Set " << i << ":\n";
		solve();
		cout << '\n';
	}
}