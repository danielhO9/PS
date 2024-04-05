#include <bits/stdc++.h>
using namespace std;

int calc(const char i) {
	if (i == 'A') return 0;
	if (i == 'C') return 1;
	if (i == 'G') return 2;
	return 3;
}

struct TrieNode {
	TrieNode* children[4];
	TrieNode* failure;
	bool terminal;
	TrieNode(): terminal(false) {
		for (int i = 0; i < 4; ++i) children[i] = NULL;
	}
	~TrieNode() {
		for (int i = 0; i < 4; ++i) if (children[i]) delete children[i];
	}
	void insert(const char* key) {
		if (*key == 0) terminal = true;
		else {
			int next = calc(*key);
			if (!children[next]) children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}
};

void getFailure(TrieNode* trie) {
	queue<TrieNode*> Q;
	trie->failure = trie;
	for (auto there: trie->children) if (there) {
		there->failure = trie;
		Q.push(there);
	}
	while(!Q.empty()) {
		TrieNode* here = Q.front(); Q.pop();
		for (int i = 0; i < 4; ++i) if (here->children[i]) {
			TrieNode* p = here->failure;
			while (p != trie && !p->children[i]) p = p->failure;
			if (p->children[i]) p = p->children[i];
			else p = trie;
			here->children[i]->failure = p;
			if (p->terminal) here->children[i]->terminal = true;
			Q.push(here->children[i]);
		}
	}
}

int query(string& s, TrieNode* trie) {
	int ret = 0;
	TrieNode* p = trie;
	for (auto& i: s) {
		int nxt = calc(i);
		while (p != trie && !p->children[nxt]) p = p->failure;
		if (p->children[nxt]) p = p->children[nxt];
		else p = trie;
		if (p->terminal) ++ret;
	}
	return ret;
}

void solve() {
	TrieNode* trie = new TrieNode();
	int n, m; cin >> n >> m;
	string DNA; cin >> DNA;
	string marker; cin >> marker;
	trie->insert(marker.c_str());
	for (int i = 0; i < m; ++i) for (int j = i + 1; j < m; ++j) {
		string temp = "";
		for (int k = 0; k < i; ++k) temp += marker[k];
		for (int k = j; k >= i; --k) temp += marker[k];
		for (int k = j + 1; k < m; ++k) temp += marker[k];
		// cout << temp << '\n';
		trie->insert(temp.c_str());
	}
	getFailure(trie);
	cout << query(DNA, trie) << '\n';
	delete trie;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}