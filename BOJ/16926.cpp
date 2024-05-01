#include <bits/stdc++.h>
using namespace std;

int N, M, R;
int arr[300][300];

void solve() {
	int R; cin >> N >> M >> R;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> arr[i][j];
	for (int i = 0; i < min(N, M) / 2; ++i) {
		vector<pair<int, int>> Q;
		deque<int> val;
		int ny = i, nx = i;
		Q.push_back({ny, nx});
		val.push_back(arr[ny][nx]);
		while (nx + 1 < M - i) {
			Q.push_back({ny, ++nx});
			val.push_back(arr[ny][nx]);
		}
		while (ny + 1 < N - i) {
			Q.push_back({++ny, nx});
			val.push_back(arr[ny][nx]);
		}
		while (nx - 1 >= i) {
			Q.push_back({ny, --nx});
			val.push_back(arr[ny][nx]);
		}
		while (ny - 1 >= i) {
			Q.push_back({--ny, nx});
			val.push_back(arr[ny][nx]);
		}
		Q.pop_back(); val.pop_back();
		for (int i = 0; i < R % ((int) Q.size()); ++i) {
			int tmp = val.front(); val.pop_front();
			val.push_back(tmp);
		}
		for (int i = 0; i < Q.size(); ++i) {
			arr[Q[i].first][Q[i].second] = val[i];
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) cout << arr[i][j] << ' ';
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}