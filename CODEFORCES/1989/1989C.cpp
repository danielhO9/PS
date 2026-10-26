#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];
	vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
	int anum = 0, bnum = 0;
	int mcnt = 0, pcnt = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] == 0 && b[i] == 0) continue;
		if (a[i] != b[i] && a[i] < 0) {
			bnum += b[i];
			continue;
		}
		if (a[i] != b[i] && b[i] < 0) {
			anum += a[i];
			continue;
		}
		if (a[i] == 0 && b[i] == 1) {
			++bnum;
			continue;
		}
		if (a[i] == 1 && b[i] == 0) {
			++anum;
			continue;
		}
		if (a[i] == 1 && b[i] == 1) ++pcnt;
		if (a[i] == -1 && b[i] == -1) ++mcnt;
	}
	if (anum < bnum) swap(anum, bnum);
	if (anum - bnum < pcnt) {
		pcnt -= anum - bnum;
		if (pcnt % 2 == 1) {
			anum += pcnt / 2; ++anum;
			bnum = anum - 1;
		} else {
			anum += pcnt / 2;
			bnum = anum;
		}
	} else {
		bnum += pcnt;
	}
	if (anum - bnum > mcnt) {
		cout << bnum << '\n';
		return;
	}
	mcnt -= anum - bnum;
	if (mcnt % 2 == 1) {
		cout << bnum - mcnt / 2 - 1 << '\n';
	} else {
		cout << bnum - mcnt / 2 << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}