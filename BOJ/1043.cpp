#include <bits/stdc++.h>
using namespace std;
int N, M, p[51];
vector<int> par[50];

int find(int v) {
	if (p[v] == v) return v;
	return p[v] = find(p[v]);;
}

void uni(int v, int u) {
	int pu = find(u), pv = find(v);
	p[pv] = min(pu, pv); p[pu] = min(pu, pv);
}

int solution(int m) {
	for (auto i: par[m]) if (!find(i)) return 0;
	return 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) p[i] = i;
	int T; cin >> T; int temp;
	for (int i = 0; i < T; ++i) {
		cin >> temp;
		p[temp] = 0;
	}
	int ttemp;
	for (int i = 0; i < M; ++i) {
		cin >> temp;
		for (int j = 0; j < temp; ++j) {
			cin >> ttemp;
			par[i].push_back(ttemp);
			if (par[i].size() > 1) uni(par[i][j - 1], par[i][j]);
		}
	}
	int ans = 0;
	for (int i = 0; i < M; ++i) ans += solution(i);
	cout << ans;
}