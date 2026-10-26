#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N;
ll K;
int a[50][50];
ll cache[50][50][60];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> a[i][j];
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cache[i][j][0] = a[i][j];
	for (int k = 1; k < 60; ++k) {
		for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
			cache[i][j][k] = 0;
			for (int l = 0; l < N; ++l) {
				cache[i][j][k] += (cache[i][l][k - 1] * cache[l][j][k - 1]) % MOD;
				cache[i][j][k] %= MOD;
			}
		}
	}
	vector<ll> ans(N, 1);
	for (ll k = 0; k < 60; ++k) if ((K >> k) & 1) {
		vector<ll> nans(N);
		for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
			nans[j] += (ans[i] * cache[i][j][k]) % MOD;
			nans[j] %= MOD;
		}
		ans = nans;
	}
	ll sum = 0;
	for (int i = 0; i < N; ++i) {
		sum += ans[i];
		sum %= MOD;
	}
	cout << sum;
}