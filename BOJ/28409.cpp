#include <bits/stdc++.h>
using namespace std;

int N, M;
int W[200000], H[200000];
int w[200000], h[200000];
int green[200000];
int height[200000];
vector<int> gray[200000];
unordered_map<int, bool> isend;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> W[i] >> H[i];
		if (i != 0) {
			W[i] += W[i - 1];
		}
		isend[W[i]] = true;
	}
	cin >> M;
	for (int i = 0; i < M; ++i) {
		cin >> w[i] >> h[i];
		if (i != 0) {
			w[i] += w[i - 1];
		}
	}
	for (int i = 0; i < M; ++i) {
		if (!isend[w[i]]) {
			cout << -1;
			return;
		}
	}

	int idx = 0;
	for (int i = 0; i < N; ++i) {
		if (W[i] > w[idx]) ++idx;
		green[i] = idx;
		gray[idx].push_back(i);
	}

	vector<int> mex;
	if (M == 1) mex.push_back(0);
	else if (M == 2) {
		if (h[1] > h[0]) mex.push_back(1);
		else mex.push_back(0);
	} else {
		if (h[0] > h[1]) mex.push_back(0);
		for (int i = 1; i < M - 1; ++i) {
			if (h[i - 1] < h[i] && h[i] > h[i + 1]) {
				mex.push_back(i);
			}
		}
		if (h[M - 1] > h[M - 2]) mex.push_back(M - 1);
	}
	vector<int> Mex;
	for (auto i: mex) {
		for (auto j: gray[i]) {
			if (H[j] == h[i]) {
				Mex.push_back(j);
				break;
			}
		}
	}
	for (int i = 0; i < Mex.size(); ++i) {
		int l, r, val;
		if (i + 1 == Mex.size()) {
			l = Mex[i];
			r = N;
			val = H[l];
		} else {
			l = Mex[i];
			r = Mex[i + 1];
			val = H[l];
		}
		for (auto j = l; j < r; ++j) {
			val = min(val, H[j]);
			height[j] = max(height[j], val);
		}
	}
	for (int i = 0; i < Mex.size(); ++i) {
		int l, r, val;
		if (i == 0) {
			l = -1;
			r = Mex[i];
			val = H[r];
		} else {
			l = Mex[i - 1];
			r = Mex[i];
			val = H[r];
		}
		for (auto j = r; j > l; --j) {
			val = min(val, H[j]);
			height[j] = max(height[j], val);
		}
	}
	for (int i = 0; i < N; ++i) {
		if (height[i] != h[green[i]]) {
			cout << -1;
			return;
		}
	}
	cout << Mex.size() << '\n';
	for (auto i: Mex) cout << i + 1 << ' ';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	solve();
	return 0;
}