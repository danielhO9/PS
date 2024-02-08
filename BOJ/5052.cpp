#include <bits/stdc++.h>
using namespace std;

void add(vector<vector<int>>& trie, vector<int>& final, int& treesize, const string& s) {
    int v = 0;
    for (auto c : s) {
        int i = c - '0';
        if (trie[v][i] == -1)
            trie[v][i] = ++treesize;
        v = trie[v][i];
    }
	final[v] = true;
}

bool check(vector<vector<int>>& trie, vector<int>& final, const string& s) {
    int v = 0;
	for (auto c: s) {
		int i = c - '0';
		if (trie[v][i] == -1) return false;
		v = trie[v][i];
		if (final[v]) return true;
	}
	return false;
}

void solve() {
	int n; cin >> n;
	vector<vector<int>> trie(100001, vector<int> (10, -1));
	vector<int> final(100001, false);
	int treesize = 0;
	vector<string> V;
	for (int i = 0; i < n; ++i) {
		string s; cin >> s;
		V.push_back(s);
	}
	sort(V.begin(), V.end());
	for (auto i: V) {
		if (check(trie, final, i)) {
			cout << "NO\n"; return;
		}
		add(trie, final, treesize, i);
	}
	cout << "YES\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}