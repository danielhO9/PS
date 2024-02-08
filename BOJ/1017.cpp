#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 50;

int n, m;
bool adj[MAX_N][MAX_N];

vector<int> aMatch, bMatch;
vector<bool> visited;

bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; ++b) {
		if (adj[a][b]) {
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
		}
	}
	return false;
}

int bipartiteMatch() {
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);
	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n, false);
		if (dfs(start)) ++size;
	}
	return size;
}

vector<bool> isPrime(2001, 1);

void init() {
	isPrime[0] = 0; isPrime[1] = 0;
	for (int i = 2; i <= 2000; ++i) {
		if (!isPrime[i]) continue;
		for (int j = 2 * i; j <= 2000; j += i) {
			isPrime[j] = 0;
		}
	}
}

void solve() {
	init();
	int N; cin >> N;
	n = N, m = N;
	vector<int> arr;
	int ocnt = 0, ecnt = 0;
	for (int i = 0; i < N; ++i) {
		int num; cin >> num;
		arr.push_back(num);
		if (num % 2 == 0) ++ecnt;
		else ++ocnt;
	}
	vector<int> avail;
	for (int i = 1; i < N; ++i) {
		if (isPrime[arr[0] + arr[i]]) avail.push_back(i);
	}
	int t = arr[0] % 2;
	for (int i = 1; i < N; ++i) {
		if (t != arr[i] % 2) continue;
		for (int j = 0; j < N; ++j) if (j != i) {
			if (isPrime[arr[i] + arr[j]]) {
				adj[i][j] = true;
			}
		}
	}
	vector<int> ans;
	for (auto i: avail) {
		adj[0][i] = 1;
		if (bipartiteMatch() == N / 2) ans.push_back(arr[i]);
		adj[0][i] = 0;
	}
	sort(ans.begin(), ans.end());
	for (auto i: ans) cout << i << ' ';
	if (ans.empty()) cout << -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}