#include <bits/stdc++.h>
using namespace std;

int trie[1000001][26], same, cnt;
int treesize, sum[1000001];
vector<string> v;

void add(const string& s) {
    int v = 0;
	++sum[v];
    for (auto c : s) {
        int i = c - 'a';
        if (trie[v][i] == -1)
            trie[v][i] = treesize++;
        v = trie[v][i];
		++sum[v];
    }
}

void update(const string& s) {
	int v = 0;
	for (int c = 0; c < s.length(); ++c) {
		int i = s[c] - 'a';
		int nxtV = trie[v][i];
		if (c != 0 && sum[v] == sum[nxtV]) ++same;
		v = nxtV;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; string temp;
	while (cin >> t) {
		memset(trie, -1, sizeof(trie));
		memset(sum, 0, sizeof(sum));
		treesize = 1; v.clear(); cnt = 0;
		for (int i = 0; i < t; ++i) {
			cin >> temp;
			cnt += temp.length();
			v.push_back(temp);
			add(temp);
		}
		same = 0;
		for (int i = 0; i < t; ++i) update(v[i]);
		cout << fixed; cout.precision(2);
		cout << (double) (cnt - same) / v.size() << '\n';
	}
}