#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	ll N; cin >> N;
	ll tmp = N / 4;
	ll ans = 2 * tmp * tmp - 2 * tmp + 1;
	if (N < 4) cout << 0;
	else if (N % 4 == 0) cout << ans;
	else if (N % 4 == 1) cout << ans + tmp - 1;
	else if (N % 4 == 2) cout << ans + 2 * tmp - 1;
	else cout << ans + 3 * tmp - 1;
}