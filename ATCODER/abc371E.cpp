#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
vector<ll> arr[200001];
ll A[200000];

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) cin >> A[i];
	for (int i = 0; i < N; ++i) {
		arr[A[i]].push_back(i);
	}
	ll ans = 0;
	for (int i = 1; i <= 2e5; ++i) {
		for (int j = 0; j < arr[i].size(); ++j) {
			if (j == 0) {
				ans += (N - arr[i][j]) * (arr[i][j] + 1);
			} else {
				ans += (N - arr[i][j]) * (arr[i][j] - arr[i][j - 1]);
			}
		}
	}
	cout << ans;
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}