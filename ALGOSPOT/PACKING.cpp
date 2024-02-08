#include <bits/stdc++.h>
using namespace std;

int N, W, v[100], d[100], cache[1001][100];
string name[100];
vector<string> answer;

int matchCache(int c, int n) {
	if (n == N) return 0;
	int& ret = cache[c][n];
	if (ret != -1) return ret;
	ret = matchCache(c, n + 1);
	if (v[n] <= c) ret = max(ret, matchCache(c - v[n], n + 1) + d[n]);
	return ret;
}

void reconstruct(int c, int n, vector<string>& answer) {
	if (n == N) return;
	if (matchCache(c, n) == matchCache(c, n + 1)) reconstruct(c, n + 1, answer);
	else {
		answer.push_back(name[n]);
		reconstruct(c - v[n], n + 1, answer);
	}
}

void solution() {
	memset(cache, -1, sizeof(cache));
	cout << matchCache(W, 0) << " ";
	answer.clear();
	reconstruct(W, 0, answer);
	cout << answer.size() << "\n";
	for (auto i: answer) cout << i << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int C; cin >> C;
	for (int i = 0; i < C; ++i) {
		cin >> N >> W;
		for (int j = 0; j < N; ++j) cin >> name[j] >> v[j] >> d[j];
		solution();
	}
}