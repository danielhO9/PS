#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll K;
int X[200001];
int A[200001];
int f[60][200001];
int Ap[200001];

void solve() {
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) cin >> X[i];
	for (int i = 1; i <= N; ++i) cin >> A[i];

	for (int i = 1; i <= N; ++i) f[0][i] = X[i];
	for (int i = 1; i < 60; ++i) {
		for (int j = 1; j <= N; ++j) {
			f[i][j] = f[i - 1][f[i - 1][j]];
		}
	}
	for (int i = 0; i < 60; ++i) {
		if ((K >> i) & 1) {
			for (int j = 1; j <= N; ++j) {
				Ap[j] = A[f[i][j]];
			}
			for (int j = 1; j <= N; ++j) A[j] = Ap[j];
		}
	}
	for (int i = 1; i <= N; ++i) cout << A[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}