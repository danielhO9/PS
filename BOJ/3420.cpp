#include <bits/stdc++.h>
using namespace std;

int N;
int V[5], R[5];
int D[5];

void solve() {
	for (int i = 0; i < N; ++i) cin >> V[i] >> R[i];
	if (N == 1) {
		cout << "NUM " << abs(R[0] - V[0]) << '\n';
		if (R[0] >= V[0]) cout << "ADD\n";
		else cout << "SUB\n";
		cout << "END\n\n";
		return;
	}
	for (int i = 0; i < N; ++i) {
		D[i] = 1;
		for (int j = 0; j < N; ++j) if (j != i) D[i] *= (V[i] - V[j]);
	}
	for (int i = 0; i < N; ++i) {
		cout << "DUP\n";
		for (int j = 0; j < N; ++j) if (j != i) {
			cout << "DUP\n";
			cout << "NUM " << V[j] << '\n';
			cout << "SUB\n";
			cout << "SWP\n";
		}
		cout << "POP\n";
		for (int j = 0; j < N - 2; ++j) cout << "MUL\n";
		cout << "NUM " << abs(D[i]) << '\n';
		cout << "DIV\n";
		if (D[i] < 0) cout << "INV\n";
		cout << "NUM " << R[i] << '\n';
		cout << "MUL\n";
		cout << "SWP\n";
	}
	cout << "POP\n";
	for (int i = 0; i < N - 1; ++i) cout << "ADD\n";
	cout << "END\n\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> N;
		if (N == 0) break;
		solve();
	}
}