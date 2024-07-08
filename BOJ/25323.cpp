#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A[500000], B[500000];

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

void solve() {
	int N; cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
		B[i] = A[i];
	}
	sort(B, B + N);
	for (int i = 0; i < N; ++i) {
		ll g = gcd(A[i], B[i]);
		ll a = A[i] / g, b = B[i] / g;
		ll sa = sqrt(a), sb = sqrt(b);
		if (sa * sa != a || sb * sb != b) {
			cout << "NO";
			return;
		}
	}
	cout << "YES";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}