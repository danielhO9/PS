#include <bits/stdc++.h>
using namespace std;

string to_binary(int num) {
	string ans = "";
	for (int i = 19; i >= 0; --i) {
		if ((num | (1 << i)) == num) ans += "1";
		else ans += "0";
	}
	return ans;
}

void add(vector<vector<int>>& trie, int& treesize, const string& s) {
    int v = 0;
    for (auto c : s) {
        int i = c - '0';
        if (trie[v][i] == -1)
            trie[v][i] = ++treesize;
        v = trie[v][i];
    }
}

int check(vector<vector<int>>& trie, int x) {
    int v = 0;
	for (int i = 19; i >= 0; --i) {
		int j = (x >> i) & 1;
		if (trie[v][j ^ 1] != -1) j ^= 1;
		x ^= j << i;
		v = trie[v][j];
	}
	return x;
}

void solve() {
	int n; cin >> n;
	vector<int> a(n, 0);
	vector<vector<int>> trie(4000001, vector<int> (2, -1));
	int treesize = 0;
	for (int i = 1; i < n; ++i) {
		cin >> a[i];
		a[i] ^= a[i - 1];
	}
	for (auto i: a) add(trie, treesize, to_binary(i));
	for (int i = 0; i < n; ++i) {
		if (check(trie, i) == n - 1) {
			for (int j: a) cout << (i ^ j) << ' ';
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solve();
}