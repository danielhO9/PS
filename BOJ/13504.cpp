#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
	TrieNode* children[2];
	bool terminal;
	TrieNode(): terminal(false) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < 2; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			int next = *key - '0';
			if (children[next] == NULL) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
	int query(const char* key, int dep) {
		if (*key == 0) return 0;
		int next = *key - '0';
		int rev = 1 - next;
		int ret = 0;
		if (children[rev] != NULL) {
			ret += (1 << dep);
			// cout << dep << ' ' << rev << '\n';
			ret += children[rev]->query(key + 1, dep - 1);
		} else {
			// cout << dep << ' ' << next << '\n';
			ret += children[next]->query(key + 1, dep - 1);
		}
		return ret;
	}
};

void solve() {
	TrieNode* trie = new TrieNode();
	int N; cin >> N;
	int ans = 0;
	int tmp = 0;
	string s;
	for (int j = 31; j >= 0; --j) s += '0';
	trie->insert(s.c_str());
	for (int i = 0; i < N; ++i) {
		int A; cin >> A;
		A ^= tmp;
		tmp = A;
		string s;
		for (int j = 31; j >= 0; --j) {
			if ((A >> j) & 1) s += '1';
			else s += '0';
		}
		trie->insert(s.c_str());
		ans = max(ans, trie->query(s.c_str(), 31));
	}
	cout << ans << '\n';
	delete trie;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}