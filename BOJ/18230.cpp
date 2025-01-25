#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, A, B;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> A >> B;
	vector<ll> a(A), b(B);
	for (int i = 0; i < A; ++i) cin >> a[i];
	for (int i = 0; i < B; ++i) cin >> b[i];
	sort(a.begin(), a.end()); reverse(a.begin(), a.end());
	sort(b.begin(), b.end()); reverse(b.begin(), b.end());
	for (int i = 1; i < A; ++i) a[i] += a[i - 1];
	for (int i = 1; i < B; ++i) b[i] += b[i - 1];
	ll ans = 0;
	for (int i = 0; i <= N / 2; ++i) {
		int j = N - i * 2;
		if (i <= B && j <= A) {
			ans = max(ans, (j != 0 ? a[j-1] : 0) + (i != 0 ? b[i-1] : 0));
		}
	}
	cout << ans;
}