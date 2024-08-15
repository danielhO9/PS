#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// returns {gcd, x, y}
tuple<ll, ll, ll> extended_euclidean(ll a, ll b) {
    if (b == 0)
        return {a, 1, 0};
    auto [g, x, y] = extended_euclidean(b, a%b);
    return {g, y, x-(a/b)*y};
}

void solve() {
	ll N, A; cin >> N >> A;
	auto [g, x, y] = extended_euclidean(A, N);
	if (g == 1) {
		if (x < 0) {
			x += (abs(x)+N-1) / N * N;
		}
		cout << N - A << ' ' << x;
	} else {
		cout << N - A << ' ' << -1;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}