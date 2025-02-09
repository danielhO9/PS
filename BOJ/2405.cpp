#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll A[100000];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> A[i];
	sort(A, A + n);
	ll ans = abs(A[1] * 2 - A[0] - A[2]);
	for (int i = 1; i < n - 1; ++i) {
		ans = max(ans, abs(A[i] * 2 - A[0] - A[i + 1]));
		ans = max(ans, abs(A[i] * 2 - A[n - 1] - A[i - 1]));
	}
	cout << ans;
}