#include <bits/stdc++.h>
using namespace std;

int ctrie[4000001][26], ntrie[4000001][26], treesize, C, N, Q;
bool check[4000001][2];
int isColor[2001];

void add(const string& s, int t) {
    int v = 0;
    for (auto c : s) {
        int i = c - 'a';
		if (t == 0) {
			if (ctrie[v][i] == 0) ctrie[v][i] = treesize++;
        	v = ctrie[v][i];
		} else {
			if (ntrie[v][i] == 0) ntrie[v][i] = treesize++;
        	v = ntrie[v][i];
		}
    }
	check[v][t] = 1;
}

void colorCheck(const string& s) {
	int v = 0;
	for (int c = 0; c < s.length(); ++c) {
		int i = s[c] - 'a';
		int V = ctrie[v][i];
		if (V == 0) return;
		if (check[V][0]) isColor[c] = 1;
		v = V;
	}
}

string solve(const string& s) {
	int v = 0;
	for (int c = 0; c < s.length(); ++c) {
		int i = s[c] - 'a';
		int V = ntrie[v][i];
		if (V == 0) break;
		if (check[V][1] && ((int) s.length()) - 2 - c >= 0 && isColor[((int) s.length()) - 2 - c]) return "Yes";
		v = V;
	}
	return "No";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> C >> N; string temp;
	treesize = 1;
	for (int i = 0; i < C; ++i) {
		cin >> temp;
		add(temp, 0);
	}
	treesize = 1;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		reverse(temp.begin(), temp.end());
		add(temp, 1);
	}
	cin >> Q;
	for (int i = 0; i < Q; ++i) {
		cin >> temp;
		memset(isColor, 0, sizeof(isColor));
		colorCheck(temp);
		reverse(temp.begin(), temp.end());
		cout << solve(temp) << '\n';
	}
}