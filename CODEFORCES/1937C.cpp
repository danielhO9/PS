#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

int query(int a, int b, int c, int d) {
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << endl;
	char ret; cin >> ret;
	if (ret == '<') return -1;
	if (ret == '=') return 0;
	else return 1;
}

void solve() {
	cin >> n;
	int maxInd = 0;
	for (int i = 1; i < n; ++i) {
		int res = query(maxInd, maxInd, i, i);
		if (res == -1) maxInd = i;
	}
	vector<int> pos;
	pos.push_back(0);
	for (int i = 1; i < n; ++i) {
		int res = query(maxInd, pos.front(), maxInd, i);
		if (res == -1) {
			pos.clear();
			pos.push_back(i);
		} else if (res == 0) {
			pos.push_back(i);
		}
	}
	int ans = pos.front();
	for (int i = 1; i < pos.size(); ++i) {
		int res = query(ans, ans, pos[i], pos[i]);
		if (res != -1) {
			ans = pos[i];
		}	
	}
	cout << "! " << ans << ' ' << maxInd << endl;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}