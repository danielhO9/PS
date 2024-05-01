#include <bits/stdc++.h>
using namespace std;

int ret = 0;
int arr[100][100];
bool filled[100][100];
int N, L;

void query(int i) {
	for (int j = 0; j < N - 1; ++j) if (abs(arr[i][j] - arr[i][j + 1]) > 1) return;
	int cnt = 0, last = -1;
	for (int j = 0; j < N - 1; ++j) {
		if (last != arr[i][j]) {
			cnt = 0; last = arr[i][j];
		}
		++cnt;
		if (arr[i][j] + 1 == arr[i][j + 1]) {
			if (cnt < L) return;
			for (int k = 0; k < L; ++k) {
				filled[i][j - k] = true;
			}
		}
	}
	cnt = 0, last = -1;
	for (int j = N - 1; j > 0; --j) {
		if (last != arr[i][j]) {
			cnt = 0; last = arr[i][j];
		}
		++cnt;
		if (arr[i][j] + 1 == arr[i][j - 1]) {
			if (cnt < L) return;
			for (int k = 0; k < L; ++k) {
				if (filled[i][j + k]) return;
			}
		}
	}
	++ret;
}

void solve() {
	cin >> N >> L;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> arr[i][j];
	memset(filled, 0, sizeof(filled));
	for (int i = 0; i < N; ++i) query(i);
	int tarr[N][N]; for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tarr[i][j] = arr[i][j];
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) arr[j][N - 1 - i] = tarr[i][j];
	memset(filled, 0, sizeof(filled));
	for (int i = 0; i < N; ++i) query(i);
	cout << ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}