#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll arr[201][201];
ll sm[201][201];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) cin >> arr[i][j];
	ll ans = arr[1][1];
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) sm[i][j] = sm[i][j - 1] + arr[i][j];
		for (int j = 1; j <= M; ++j) sm[i][j] += sm[i - 1][j];
	}
	for (int i = 1; i <= N; ++i) for (int j = 1; j <= M; ++j) {
		for (int ni = 0; ni < i; ++ni) for (int nj = 0; nj < j; ++nj) {
			ans = max(ans, sm[i][j] + sm[ni][nj] - sm[i][nj] - sm[ni][j]);
		}
	}
	cout << ans;
}