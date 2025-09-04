#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;
const int MAX_M = 1000;

int aMatch[MAX_N], bMatch[MAX_M];
bool vis[MAX_N];
vector<int> adj[MAX_N];

bool dfs(int a) {
	if (vis[a]) return false;
	vis[a] = true;
	for (auto b: adj[a]) {
		if (bMatch[b] == -1 || dfs(bMatch[b])) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}
	return false;
}

// time complexity: V*E
int bipartiteMatch(int N, int M) {
	for (int i = 0; i < N; ++i) aMatch[i] = -1;
	for (int i = 0; i < M; ++i) bMatch[i] = -1;
	int size = 0;
	for (int i = 0; i < N; ++i) vis[i] = false;
	for (int start = 0; start < N; ++start) {
		if (dfs(start)) {
			++size;
			for (int i = 0; i < N; ++i) vis[i] = false;
		}
	}
	return size;
}

int N;
int match[1000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int A; cin >> A;
        for (int j = 0; j < A; ++j) {
            int k; cin >> k; --k;
            adj[i].push_back(k);
        }
    }
    for (int i = 0; i < N; ++i) sort(adj[i].begin(), adj[i].end());
    int sz = bipartiteMatch(N, N);
    if (sz != N) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < N; ++i) match[i] = aMatch[i];
    for (int i = 0; i < N; ++i) reverse(adj[i].begin(), adj[i].end());
    bipartiteMatch(N, N);
    for (int i = 0; i < N; ++i) if (aMatch[i] != match[i]) {
        cout << -1;
        return 0;
    }
    cout << 1 << '\n';
    for (int i = 0; i < N; ++i) cout << match[i] + 1 << ' ';
}