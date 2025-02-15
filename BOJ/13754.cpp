#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll k[1000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n; for (int i = 0; i < n; ++i) cin >> k[i];
	ll mx = *max_element(k, k + n);
	ll sm = 0; for (int i = 0; i < n; ++i) sm += k[i];
	if (mx * 2 > sm) cout << sm - mx;
	else cout << sm / 2;
}