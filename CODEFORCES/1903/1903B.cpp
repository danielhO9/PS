#include <bits/stdc++.h>
using namespace std;

int n, M[1000][1000], a[1000];

void solution() {
	cin >> n;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> M[i][j];
	for (int i = 0; i < n; ++i) a[i] = (1 << 30) - 1;
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j) a[i] &= M[i][j];
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j) {
		if ((a[i] | a[j]) != M[i][j]) {
			cout << "NO" << '\n';
			return;
		}
	}
	cout << "YES" << '\n';
	for (int i = 0; i < n; ++i) cout << a[i] << " ";
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	for (int i = 0; i < t; ++i) solution();
}