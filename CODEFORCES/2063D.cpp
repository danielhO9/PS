#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[200000];
ll b[200000];
int al, ar, au, bl, br, bu;

ll apos() {
	if (br - bl + 1 - bu >= 1 && ar - al + 1 - au >= 2) return a[ar] - a[al];	
	else return 0;
}

ll bpos() {
	if (br - bl + 1 - bu >= 2 && ar - al + 1 - au >= 1) return b[br] - b[bl];	
	else return 0;
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < m; ++i) cin >> b[i];
	sort(a, a + n); sort(b, b + m);

	ll kmax;
	ll mx = max(n, m), mn = min(n, m);
	if (mx >= 2 * mn) kmax = mn;
	else kmax = (m + n) / 3;
	cout << kmax << '\n';
	al = 0, ar = n - 1, au = 0;
	bl = 0, br = m - 1, bu = 0;
	vector<ll> ap, bp;
	ll val = 0;
	vector<ll> ans;
	for (int i = 1; i <= kmax; ++i) {
		ll aval = apos(), bval = bpos();
		if (aval == 0 && bval == 0) {
			if (br - bl + 1 - bu >= 2) {
				val -= ap.back(); ap.pop_back(); ++ar; --al; --bu;
				bp.push_back(b[br] - b[bl]);
				val += b[br] - b[bl]; --br; ++bl; ++au;
				bp.push_back(b[br] - b[bl]);
				val += b[br] - b[bl]; --br; ++bl; ++au;
			} else {
				val -= bp.back(); bp.pop_back(); ++br; --bl; --au;
				ap.push_back(a[ar] - a[al]);
				val += a[ar] - a[al]; --ar; ++al; ++bu;
				ap.push_back(a[ar] - a[al]);
				val += a[ar] - a[al]; --ar; ++al; ++bu;
			}
		} else {
			if (aval > bval) {
				ap.push_back(a[ar] - a[al]);
				val += a[ar] - a[al]; --ar; ++al; ++bu;
			} else {
				bp.push_back(b[br] - b[bl]);
				val += b[br] - b[bl]; --br; ++bl; ++au;
			}
		}
		ans.push_back(val);
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';


}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}