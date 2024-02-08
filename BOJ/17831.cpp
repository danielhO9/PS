#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> graph[200001];
vector<int> A(200001);
vector<vector<int>> cache(200001, vector<int>(2, -1));

int matchCache(int v, int t) {
	int& ret = cache[v][t];
	if (ret != -1) return ret;
	ret = 0; for (auto i: graph[v]) ret += matchCache(i, 1);
	if (t == 0) return ret;
	int sum = ret;
	for (auto i: graph[v]) ret = max(ret, sum - matchCache(i, 1) + A[i] * A[v] + matchCache(i, 0));
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 2; i <= N; ++i) {
		int p; cin >> p;
		graph[p].push_back(i);
	}
	for (int i = 1; i <= N; ++i) cin >> A[i];
	cout << matchCache(1, 1);
}