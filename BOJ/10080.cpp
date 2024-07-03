#include <bits/stdc++.h>
using namespace std;

bool A[50][50], B[50][50];



void solve() {
	int N, M; cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> B[i][j];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}