#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
	if (a < b) swap(a, b);
	if (b == 0) return a;
	return gcd(b, a % b);
}

int N;
ll A[100];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	pair<ll, ll> d = {A[1], A[0]};
	ll g = gcd(A[1], A[0]);
	d.first /= g; d.second /= g;
	for (int i = 0; i < N - 1; ++i) {
		if (A[i] % d.second != 0 || A[i] / d.second * d.first != A[i + 1]) {
			cout << "No";
			return;
		}
	}
	cout << "Yes";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}