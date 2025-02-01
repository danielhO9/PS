#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
char S[50][50];
char T[50][50];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		for (int j = 0; j < N; ++j) S[i][j] = s[j];
	}
	for (int i = 0; i < M; ++i) {
		string s; cin >> s;
		for (int j = 0; j < M; ++j) T[i][j] = s[j];
	}
	int ansi, ansj;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		bool flag = true;
		for (int k = 0; k < M; ++k) for (int l = 0; l < M; ++l) {
			if (i + k >= N || j + l >= N || S[i + k][j + l] != T[k][l]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			ansi = i, ansj = j;
		}
	}
	cout << ansi + 1 << ' ' << ansj + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}