#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 9;

vector<vector<ll>> A(167, vector<ll>(167, 0));
vector<vector<ll>> I(167, vector<ll>(167, 0));

vector<vector<ll>> mat_mul(vector<vector<ll>>& X, vector<vector<ll>>& Y) {
	assert(X[0].size() == Y.size());
	vector<vector<ll>> ret(X.size(), vector<ll>(Y[0].size(), 0));
	for (int i = 0; i < X.size(); ++i) for (int j = 0; j < Y[0].size(); ++j) for (int k = 0; k < X[0].size(); ++k) {
		ret[i][j] += (X[i][k] * Y[k][j]) % MOD;
		ret[i][j] %= MOD;
	}
	return ret;
}

vector<vector<ll>> mat_pow(vector<vector<ll>>& X, ll y) {
	if (y == 0) return I;
	vector<vector<ll>> half = mat_pow(X, y / 2);

	vector<vector<ll>> half_square = mat_mul(half, half);
	if (y % 2) return mat_mul(half_square, X);
	else return half_square;
}

ll N, M, a, b, c, d, e, f;

void solve() {
	cin >> N >> M;
	cin >> a >> b >> c >> d >> e >> f;
	a %= 167; b %= 167; c %= 167;
	d %= 167; e %= 167; f %= 167;
	N %= 167;
	for (int i = 0; i < 167; ++i) I[i][i] = 1ll;

	for (ll i = 0; i < 167; ++i) {
		++A[(a * i * i + b * i + c) % 167][i];
		++A[(d * i * i + e * i + f) % 167][i];
	}
	vector<vector<ll>> ret = mat_pow(A, M);
	ll ans = 0ll;
	ll tmp = 1ll;
	for (int i = 0; i < 167; ++i) {
		ans += (ret[i][N] * tmp) % MOD;
		ans %= MOD;
		tmp *= 112345;
		tmp %= MOD;
	}
	cout << ans;

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}