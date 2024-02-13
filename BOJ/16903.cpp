#include <bits/stdc++.h>
using namespace std;

void add(vector<vector<int>>& trie, vector<int>& final, int& treesize, const string& s) {
    int v = 0;
    for (auto c : s) {
        int i = c - 'a';
        if (trie[v][i] == -1)
            trie[v][i] = ++treesize;
        v = trie[v][i];
    }
	final[v] = true;
}

bool check(vector<vector<int>>& trie, vector<int>& final, const string& s) {
    int v = 0;
	for (auto c: s) {
		int i = c - 'a';
		if (trie[v][i] == -1) return false;
		v = trie[v][i];
	}
	if (final[v]) return true;
	return false;
}

void solve() {
	int n;
	vector<vector<int>> trie(4000001, vector<int> (26, -1));
	vector<int> final(4000001, false);
	int treesize = 0;
	add(trie, final, treesize, "abc");
	cout << check(trie, final, "abc");
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}