#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;

int query(int l, int r) {
	cout << "? " << l << ' ' << r << '\n';
	cout.flush();
	int ret; cin >> ret;
	return ret;
}


void solve() {
	cin >> n;
	int q1 = query(1, n / 4);
	int q2 = query(n / 4 + 1, n / 2);
	int l, r;
	if (q1 == q2) l = n / 2 + 1, r = n;
	else l = 1, r = n / 2;
	int tmp = query(l, r);
	int s, e;
	if (tmp == 0) {
		e = n / 2;
		s = 1;
		while (s + 1 < e) {
			int mid = (s + e) / 2;
			int ll = (l == 1 ? n / 2 + 1 : 1);
			int rr = ll + mid - 1;
			tmp = query(ll, rr);
			if (tmp == 1) e = mid;
			else s = mid;
		}
		cout << "! " << e << '\n';
		cout.flush();
	} else {
		e = n - 1;
		s = n / 2 - 1;
		while (s + 1 < e) {
			int mid = (s + e) / 2;
			int ll, rr;
			if (l == 1) {
				ll = 1;
				rr = mid;
			} else {
				rr = n;
				ll = n - mid + 1;
			}
			tmp = query(ll, rr);
			if (tmp == 0) e = mid;
			else s = mid;
		}
		cout << "! " << e << '\n';
		cout.flush();
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}