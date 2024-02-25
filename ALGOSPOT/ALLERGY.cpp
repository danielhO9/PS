#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> canEat[50], eaters[50];
int best;

void search(vector<int>& edible, int chosen) {
	if (chosen >= best) return;
	int first = 0;
	while (first < n && edible[first] > 0) ++first;
	if (first == n) { best = chosen; return; }
	for (int i = 0; i < canEat[first].size(); ++i) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); ++j)
			edible[eaters[food][j]]--;
	}
}

void solve() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) canEat[i].clear();
	for (int i = 0; i < m; ++i) eaters[i].clear();
	map<string, int> M;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		M[s] = i;
	}
	for (int i = 0; i < m; ++i) {
		int c; cin >> c;
		for (int j = 0; j < c; ++j) {
			string s; cin >> s;
			eaters[i].push_back(M[s]);
			canEat[M[s]].push_back(i);
		}
	}
	best = 51; vector<int> edible(n, 0);
	search(edible, 0);
	cout << best << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}