#include <bits/stdc++.h>
using namespace std;

int N;
char star[3072][6144];

void solution(int y, int x, int n) {
	if (n == 3) {
		for (int i = 0; i < 5; ++i) star[y][x + i] = '*';
		star[y + 1][x + 1] = '*';
		star[y + 1][x + 3] = '*';
		star[y + 2][x + 2] = '*';
		return;
	}
	solution(y, x, n / 2);
	solution(y, x + n, n / 2);
	solution(y + n / 2, x + n / 2, n / 2);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	solution(0, 0, N);
	for (int i = N - 1; i >= 0; --i) {
		for (int j = 0; j < N * 2; ++j) {
			if (star[i][j]) cout << star[i][j];
			else cout << ' ';
		}
		cout << "\n";
	}
}